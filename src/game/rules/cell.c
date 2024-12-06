#include "cell.h"

int insertValue(Cell *cell, int value) {
    if (!cell->isModifiable)
        return 1;
    cell->value = value;
    for (int i = 0; i < 9; ++i)
        cell->notes[i] = false;
    return 0;
}

int removeValue(Cell *cell) {
    if (!cell->isModifiable)
        return 1;
    if (cell->value == 0)
        return 2;
    cell->value = 0;
    return 0;
}

int insertNote(Cell *cell, int noteValue) {
    if (!cell->isModifiable)
        return 1;
    if (noteValue > 9 || noteValue < 1)
        return 2;
    if (cell->notes[noteValue - 1] == 1)
        return 3;
    cell->notes[noteValue - 1] = 1;
    return 0;
}

int removeNote(Cell *cell, int noteValue) {
    if (!cell->isModifiable)
        return 1;
    if (noteValue > 9 || noteValue < 1)
        return 2;
    if (cell->notes[noteValue - 1] == 0)
        return 3;
    cell->notes[noteValue - 1] = 0;
    return 0;
}
