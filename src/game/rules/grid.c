//
// Created by felixmielcarek on 12/6/24.
//

#include "grid.h"

int insertValue(Grid *grid, const int column, const int row, const int value) {
    int sectionColumn = column / 3, sectionRow = row / 3, firstCellOfSectionColumn = sectionColumn * 3,
        firstCellOfSectionRow = sectionRow * 3;

    insertCellValue(&grid->cells[column][row], value);

    // Remove notes equal to value in cells of the same column or row
    for (int i = 0; i < 9; ++i) {
        removeNote(&grid->cells[column][i], value);
        removeNote(&grid->cells[i][row], value);
    }

    // Remove notes equal to value in cells of the same section
    for (int col = firstCellOfSectionColumn; col < firstCellOfSectionColumn + 3; ++col)
        for (int row = firstCellOfSectionRow; row < firstCellOfSectionRow + 3; ++row)
            removeNote(&grid->cells[col][row], value);

    return 0;
}
