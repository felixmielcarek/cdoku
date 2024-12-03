#include "gui.h"

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
    renderSelection(&guiElements, g, 0, 1);

    SDL_RenderPresent(guiElements.renderer);

    SDL_Delay(5000);

    return cleanExit(EXIT_SUCCESS, &guiElements);
}
