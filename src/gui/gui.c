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
            const char *pressedKeyName;
            switch (event.type) {
                case SDL_QUIT:
                    return 1;

                case SDL_KEYDOWN:
                    pressedKeyName = SDL_GetKeyName(event.key.keysym.sym);
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

int startGame(const GuiElements *guiElements) {
    Grid grid;

    getNewGrid(&grid);
    for (int i = 0; i < 9; ++i) {
        for (int y = 0; y < 9; ++y)
            fprintf(stderr, "%d ", grid.cells[i][y].value);
        fprintf(stderr, "\n");
    }

    renderGrid(guiElements, grid);
    SDL_RenderPresent(guiElements->renderer);

    return gameLoop(guiElements, grid);
}

int mainMenuLoop(const GuiElements *guiElements) {
    SDL_Event event;
    int running = 1;

    while (running) {
        while (SDL_PollEvent(&event)) {
            const char *pressedKeyName;
            switch (event.type) {
                case SDL_QUIT:
                    running = 0;
                    break;

                case SDL_KEYDOWN:
                    pressedKeyName = SDL_GetKeyName(event.key.keysym.sym);
                    fprintf(stderr, "Key pressed:\t%s\n", pressedKeyName);
                    if (strcmp(pressedKeyName, "Return") == 0) {
                        if (startGame(guiElements) == 1)
                            running = 0;
                        break;
                    }

                    break;

                case SDL_MOUSEBUTTONDOWN:
                    // Only handle left click
                    if (event.button.button != 1)
                        break;
                    // Check if in bounds
                    if (event.button.x >= MAINMENUX && event.button.x <= MAINMENUX + MAINMENUWIDTH &&
                        event.button.y >= MAINMENUY && event.button.y <= MAINMENUY + MAINMENUHEIGHT) {
                        if (startGame(guiElements) == 1)
                            running = 0;
                        break;
                    }
                    break;

                default:
                    break;
            }
        }
    }
    return 0;
}

int runGui() {
    GuiElements guiElements;

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        return exitOnSDLError(EXIT_FAILURE, &guiElements, "SDL init");

    if (TTF_Init() == -1)
        return exitOnTTFError(EXIT_FAILURE, &guiElements, "SDL TTF init");

    guiElements.window = SDL_CreateWindow("Cdoku", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOWWIDTH,
                                          WINDOWHEIGHT, SDL_WINDOW_SHOWN);
    if (guiElements.window == NULL)
        return exitOnSDLError(EXIT_FAILURE, &guiElements, "window creation");

    guiElements.renderer = SDL_CreateRenderer(guiElements.window, -1, SDL_RENDERER_ACCELERATED);
    if (guiElements.renderer == NULL)
        return exitOnSDLError(EXIT_FAILURE, &guiElements, "renderer creation");

    renderMainMenu(&guiElements);
    SDL_RenderPresent(guiElements.renderer);

    mainMenuLoop(&guiElements);

    return cleanExit(EXIT_SUCCESS, &guiElements);
}
