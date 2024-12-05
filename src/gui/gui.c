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

int gameLoop(const GuiElements *guiElements, Grid g) {
    SDL_Event event;
    int running = 1, lastSelectedCellColumn = -1, lastSelectedCellRow = -1, value;

    while (running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = 0;
                    break;

                case SDL_KEYDOWN:
                    const char *pressedKeyName = SDL_GetKeyName(event.key.keysym.sym);
                    fprintf(stderr, "Key pressed:\t%s\n", pressedKeyName);
                    value = atoi(pressedKeyName);
                    // if pressed key is a number
                    if (value != 0) {
                        // if a cell is selected
                        if (lastSelectedCellColumn != -1 && lastSelectedCellRow != -1) {
                            if (insertValue(&g.cells[lastSelectedCellColumn][lastSelectedCellRow], value) == 0) {
                                int gameResult = isGameFinished(g);
                                if (gameResult == 0)
                                    renderWunGrid(guiElements, g);
                                if (gameResult == 1)
                                    renderSelection(guiElements, g, lastSelectedCellColumn, lastSelectedCellRow);
                                if (gameResult == 2)
                                    renderLostGrid(guiElements, g);
                                SDL_RenderPresent(guiElements->renderer);
                            }
                        }
                        break;
                    }
                    if (strcmp(pressedKeyName, "Backspace") == 0 || strcmp(pressedKeyName, "Delete") == 0) {
                        if (removeValue(&g.cells[lastSelectedCellColumn][lastSelectedCellRow]) == 0) {
                            renderSelection(guiElements, g, lastSelectedCellColumn, lastSelectedCellRow);
                            SDL_RenderPresent(guiElements->renderer);
                        }
                        break;
                    }

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

int runGui(Grid g) {
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
