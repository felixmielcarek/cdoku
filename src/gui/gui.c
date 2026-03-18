#include "gui.h"

int gameLoop(const GuiElements *guiElements, Grid g) {
    SDL_Event event;
    int running = 1, lastSelectedCellColumn = -1, lastSelectedCellRow = -1;
    int insertMode = 0; // 0 = value ; 1 = note

    while (running) {
        while (SDL_PollEvent(&event)) {
            InputEvent input = processEvent(&event);

            switch (input.action) {
                case INPUT_QUIT:
                    return 1;

                case INPUT_NUMBER:
                    // if a cell is selected
                    if (lastSelectedCellColumn != -1 && lastSelectedCellRow != -1) {
                        if (insertMode == 0) {
                            if (insertValue(&g, lastSelectedCellColumn, lastSelectedCellRow, input.value) == 0) {
                                int gameResult = isGameFinished(g);
                                if (gameResult == 0)
                                    renderWunGrid(guiElements, g);
                                else if (gameResult == 1)
                                    renderSelection(guiElements, g, lastSelectedCellColumn, lastSelectedCellRow);
                                else if (gameResult == 2)
                                    renderLostGrid(guiElements, g);
                            }
                        } else if (insertNote(&g.cells[lastSelectedCellColumn][lastSelectedCellRow], input.value) == 0)
                            renderCell(guiElements, g.cells[lastSelectedCellColumn][lastSelectedCellRow],
                                       lastSelectedCellColumn, lastSelectedCellRow, CELLTEXTCOLOR,
                                       SELECTEDCELLCOLOR);
                        SDL_RenderPresent(guiElements->renderer);
                    }
                    break;

                case INPUT_ARROW_LEFT:
                    if (lastSelectedCellColumn > 0 && lastSelectedCellRow != -1) {
                        lastSelectedCellColumn--;
                        renderSelection(guiElements, g, lastSelectedCellColumn, lastSelectedCellRow);
                        SDL_RenderPresent(guiElements->renderer);
                    }
                    break;

                case INPUT_ARROW_RIGHT:
                    if (lastSelectedCellColumn < 8 && lastSelectedCellColumn != -1 && lastSelectedCellRow != -1) {
                        lastSelectedCellColumn++;
                        renderSelection(guiElements, g, lastSelectedCellColumn, lastSelectedCellRow);
                        SDL_RenderPresent(guiElements->renderer);
                    }
                    break;

                case INPUT_ARROW_UP:
                    if (lastSelectedCellRow > 0 && lastSelectedCellColumn != -1) {
                        lastSelectedCellRow--;
                        renderSelection(guiElements, g, lastSelectedCellColumn, lastSelectedCellRow);
                        SDL_RenderPresent(guiElements->renderer);
                    }
                    break;

                case INPUT_ARROW_DOWN:
                    if (lastSelectedCellRow < 8 && lastSelectedCellColumn != -1 && lastSelectedCellRow != -1) {
                        lastSelectedCellRow++;
                        renderSelection(guiElements, g, lastSelectedCellColumn, lastSelectedCellRow);
                        SDL_RenderPresent(guiElements->renderer);
                    }
                    break;

                case INPUT_DELETE:
                    if (lastSelectedCellColumn != -1 && lastSelectedCellRow != -1) {
                        if (removeValue(&g.cells[lastSelectedCellColumn][lastSelectedCellRow]) == 0) {
                            renderSelection(guiElements, g, lastSelectedCellColumn, lastSelectedCellRow);
                            SDL_RenderPresent(guiElements->renderer);
                        }
                    }
                    break;

                case INPUT_TOGGLE_NOTE:
                case INPUT_NOTE_ICON_CLICK:
                    insertMode = !insertMode;
                    renderNoteIcon(guiElements, insertMode);
                    SDL_RenderPresent(guiElements->renderer);
                    break;

                case INPUT_CELL_CLICK: {
                    int previousCellColumn = lastSelectedCellColumn, previousCellRow = lastSelectedCellRow;
                    if (getCoordonatesCell(input.x, input.y, &lastSelectedCellColumn, &lastSelectedCellRow) == 1) {
                        if (lastSelectedCellColumn == -1 || lastSelectedCellRow == -1) {
                            renderGrid(guiElements, g);
                            SDL_RenderPresent(guiElements->renderer);
                        }
                        break;
                    }

                    if (previousCellColumn != lastSelectedCellColumn || previousCellRow != lastSelectedCellRow) {
                        renderSelection(guiElements, g, lastSelectedCellColumn, lastSelectedCellRow);
                        SDL_RenderPresent(guiElements->renderer);
                    }
                    break;
                }

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

    renderBase(guiElements);
    renderGrid(guiElements, grid);
    renderNoteIcon(guiElements, 0);

    SDL_RenderPresent(guiElements->renderer);

    return gameLoop(guiElements, grid);
}

int mainMenuLoop(const GuiElements *guiElements) {
    SDL_Event event;
    int running = 1;

    while (running) {
        while (SDL_PollEvent(&event)) {
            InputEvent input = processEvent(&event);

            switch (input.action) {
                case INPUT_QUIT:
                    running = 0;
                    break;

                case INPUT_CONFIRM:
                case INPUT_MENU_CLICK:
                    if (startGame(guiElements) == 1)
                        running = 0;
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

    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
        return exitOnIMGError(EXIT_FAILURE, &guiElements, "SDL IMG init");

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
