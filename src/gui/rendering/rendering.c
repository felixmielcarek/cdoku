//
// Created by felixmielcarek on 11/28/24.
//

#include "rendering.h"

int renderSelection(const GuiElements *guiElements, const Grid grid, const int cellColumn, const int cellRow) {
    int sectionColumn = cellColumn / 3, sectionRow = cellRow / 3;

    for (int col = 0; col < 9; ++col) {
        int tmpSectionCol = col / 3;
        for (int row = 0; row < 9; ++row) {
            int tmpSectionRow = row / 3;
            if (col == cellColumn || row == cellRow || (tmpSectionCol == sectionColumn && tmpSectionRow == sectionRow))
                renderCell(guiElements, grid.cells[col][row], col, row, LINKEDSELECTEDCELLCOLOR);
            if (grid.cells[cellColumn][cellRow].value != 0 &&
                grid.cells[cellColumn][cellRow].value == grid.cells[col][row].value)
                renderCell(guiElements, grid.cells[col][row], col, row, NUMBERSELECTEDCELLCOLOR);
        }
    }
    renderCell(guiElements, grid.cells[cellColumn][cellRow], cellColumn, cellRow, SELECTEDCELLCOLOR);

    return 0;
}

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
