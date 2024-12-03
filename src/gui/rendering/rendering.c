//
// Created by felixmielcarek on 11/28/24.
//

#include "rendering.h"

int renderGrid(const GuiElements *guiElements, const Grid grid) {
    for (int col = 0; col < 9; ++col) {
        for (int row = 0; row < 9; ++row) {
            renderCellBorders(guiElements, col, row);
            renderCell(guiElements, grid.cells[col][row], col, row, CELLCOLOR);
        }
    }

    for (int sectionColumn = 0; sectionColumn < 3; ++sectionColumn)
        for (int sectionRow = 0; sectionRow < 3; ++sectionRow)
            renderSectionBorders(guiElements, sectionColumn, sectionRow);

    return 0;
}

int renderBase(const GuiElements *guiElements) {
    setRanderDrawColor(guiElements->renderer, BGCOLOR);
    SDL_RenderClear(guiElements->renderer);

    return 0;
}
