#ifndef GRID_H
#define GRID_H

#include "cell.h"

typedef struct grid {
    Cell cells[9][9];
    int solution[9][9];
} Grid;

int insertValue(Grid *grid, const int column, const int row, const int value);

#endif
