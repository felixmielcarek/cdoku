//
// Created by felixmielcarek on 11/28/24.
//

#ifndef RENDERING_H
#define RENDERING_H

#include <SDL2/SDL.h>

#include "../../game/rules/cell.h"
#include "../../game/rules/grid.h"
#include "../cellRendering/cellRendering.h"
#include "../common/common.h"
#include "../constants/constants.h"
#include "../sectionRendering/sectionRendering.h"

int renderSelection(const GuiElements *guiElements, const Grid grid, const int cellColumn, const int cellRow);
int renderBase(const GuiElements *gui_elements);
int renderMainMenu(const GuiElements *gui_elements);
int renderGrid(const GuiElements *guiElements, const Grid grid);
int renderWunGrid(const GuiElements *guiElements, const Grid grid);
int renderLostGrid(const GuiElements *guiElements, const Grid grid);

#endif // RENDERING_H
