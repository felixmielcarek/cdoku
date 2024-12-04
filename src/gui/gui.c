#include "gui.h"

int getCoordonatesCell(const int x, const int y, int *column, int *row) {
    const int noBorderX = x - GRIDX - SECTIONBORDERSIZE, // removes the outside left border of the grid
            noBorderY = y - GRIDY - SECTIONBORDERSIZE; // removes the outside top border of the grid

    if (noBorderX < 0 || noBorderY < 0 || noBorderX > 3 * SECTIONSIZE + 2 * SECTIONBORDERSIZE ||
        noBorderY > 3 * SECTIONSIZE + 2 * SECTIONBORDERSIZE) {
        *column = -1;
        *row = -1;
        return 1;
    }

    *column = noBorderX / (CELLSIZE + CELLBORDERSIZE);
    *row = noBorderY / (CELLSIZE + CELLBORDERSIZE);

    return 0;
}

int gameLoop(const GuiElements *guiElements, const Grid g) {
    SDL_Event event;
    int running = 1, lastSelectedCellColumn = -1, lastSelectedCellRow = -1;

    while (running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = 0;
                    break;

                case SDL_KEYDOWN:
                    printf("Key pressed: %s\n", SDL_GetKeyName(event.key.keysym.sym));
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    // Only handle left click
                    if (event.button.button != 1)
                        break;

                    // Check if in bounds
                    if (getCoordonatesCell(event.button.x, event.button.y, &lastSelectedCellColumn,
                                           &lastSelectedCellRow) == 1) {
                        // Check if should unselect cell
                        if (lastSelectedCellColumn == -1 || lastSelectedCellRow == -1) {
                            renderGrid(guiElements, g);
                            SDL_RenderPresent(guiElements->renderer);
                        }
                        break;
                    }

                    // Select
                    renderSelection(guiElements, g, lastSelectedCellColumn, lastSelectedCellRow);
                    SDL_RenderPresent(guiElements->renderer);
                    break;

                default:
                    break;
            }
        }
    }
    return 0;
}

int runGui(const Grid g) {
    GuiElements guiElements;

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        return exitOnSDLError(EXIT_FAILURE, &guiElements, "SDL init");

    if (TTF_Init() == -1)
        return exitOnTTFError(EXIT_FAILURE, &guiElements, "SDL TTF init");

    guiElements.window =
            SDL_CreateWindow("Cdoku", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
    if (guiElements.window == NULL)
        return exitOnSDLError(EXIT_FAILURE, &guiElements, "window creation");

    guiElements.renderer = SDL_CreateRenderer(guiElements.window, -1, SDL_RENDERER_ACCELERATED);
    if (guiElements.renderer == NULL)
        return exitOnSDLError(EXIT_FAILURE, &guiElements, "renderer creation");

    renderBase(&guiElements);
    renderGrid(&guiElements, g);
    SDL_RenderPresent(guiElements.renderer);

    gameLoop(&guiElements, g);

    return cleanExit(EXIT_SUCCESS, &guiElements);
}
