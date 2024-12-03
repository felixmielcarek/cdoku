//
// Created by felixmielcarek on 11/28/24.
//

#ifndef COMMON_H
#define COMMON_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h> // to render text with SDL

typedef struct guiElements {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *textTexture;
} GuiElements;

int cleanExit(const int result, const GuiElements *guiElements);
int exitOnError(const int result, const GuiElements *guiElements, const char *context);
int exitOnTTFError(const int result, const GuiElements *guiElements, const char *context);
int exitOnSDLError(const int result, const GuiElements *guiElements, const char *context);
int setRanderDrawColor(SDL_Renderer *renderer, const SDL_Color color);

#endif // COMMON_H
