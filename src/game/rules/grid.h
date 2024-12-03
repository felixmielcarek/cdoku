#ifndef GRID_H
#define GRID_H

#include "cell.h"

typedef struct grid {
    Cell cells[9][9];
} Grid;
#endif