//
// Created by felixmielcarek on 11/28/24.
//

#include "common.h"

int cleanExit(const int result, const GuiElements *guiElements) {
    if (guiElements->window != NULL)
        SDL_DestroyWindow(guiElements->window);
    if (guiElements->renderer != NULL)
        SDL_DestroyRenderer(guiElements->renderer);

    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
    return result;
}

int exitOnError(const int result, const GuiElements *guiElements, const char *context) {
    fprintf(stderr, "Error: %s.\n", context);
    return cleanExit(result, guiElements);
}

int exitOnIMGError(const int result, const GuiElements *guiElements, const char *context) {
    fprintf(stderr, "Error IMG [%s]: %s", context, IMG_GetError());
    return cleanExit(result, guiElements);
}

int exitOnTTFError(const int result, const GuiElements *guiElements, const char *context) {
    fprintf(stderr, "Error TTF [%s]: %s", context, TTF_GetError());
    return cleanExit(result, guiElements);
}

int exitOnSDLError(const int result, const GuiElements *guiElements, const char *context) {
    fprintf(stderr, "Error SDL [%s]: %s", context, SDL_GetError());
    return cleanExit(result, guiElements);
}

int setRanderDrawColor(SDL_Renderer *renderer, const SDL_Color color) {
    return SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}
