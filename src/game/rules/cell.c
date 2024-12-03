#include "cell.h"

int insertValue(Cell* cell, int value) {
    if(!cell->isModifiable) return 1;
	cell->value = value;
	return 0;
}

int removeValue(Cell* cell) {
    if(!cell->isModifiable) return 1;
    cell->value = 0;
    return 0;
}

int insertNote(Cell* cell, int noteValue) {
    if(!cell->isModifiable) return 1;
    if(noteValue>9 || noteValue<1) return 2;
    if(cell->notes[noteValue] == true) return 3;
    cell->notes[noteValue] = true;
    return 0;
}

int removeNote(Cell* cell, int noteValue) {
    if(!cell->isModifiable) return 1;
    if(noteValue>9 || noteValue<1) return 2;
    if(cell->notes[noteValue] == false) return 3;
    cell->notes[noteValue] = false;
    return 0;
}