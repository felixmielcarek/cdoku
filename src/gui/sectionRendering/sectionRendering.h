//
// Created by felixmielcarek on 11/30/24.
//

#ifndef SECTIONRENDERING_H
#define SECTIONRENDERING_H

#include <SDL2/SDL.h>

#include "../common/common.h"
#include "../constants/constants.h"

int renderSectionBorders(const GuiElements *guiElements, const int column, const int row, const SDL_Color borderColor);

#endif // SECTIONRENDERING_H
