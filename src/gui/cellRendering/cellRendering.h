//
// Created by felixmielcarek on 11/30/24.
//

#ifndef CELLRENDERING_H
#define CELLRENDERING_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h> // to render text with SDL

#include "../../game/rules/cell.h"
#include "../common/common.h"
#include "../constants/constants.h"

int renderCell(const GuiElements *guiElements, const Cell cell, const int column, const int row,
               const SDL_Color textColor, const SDL_Color backgroundColor);
int renderCellBorders(const GuiElements *guiElements, const int column, const int row, const SDL_Color borderColor);

#endif // CELLRENDERING_H
