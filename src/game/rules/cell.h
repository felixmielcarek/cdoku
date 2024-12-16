#ifndef CELL_H
#define CELL_H

#include <stdbool.h>

/*
 * Define a cell in the Sudoku grid.
 * The value of the cell is 0 if empty.
 */
typedef struct cell {
    bool isModifiable;
    int value;
    int notes[9];
} Cell;

/**
 * Insert the value 'value' in the cell 'cell'.
 * Return 1 if the cell is not modifiable.
 * Return 0 if ok.
 */
int insertCellValue(Cell *cell, int value);

/**
 * Set the value to 0 in the cell 'cell'.
 * Return 1 if the cell is not modifiable.
 * Return 0 if ok.
 */
int removeValue(Cell *cell);

/**
 * Set the value 1 at the 'noteValue' emplacement in notes.
 * Return 1 if the cell is not modifiable.
 * Return 2 and do not set the value if 'noteValue' makes no sense.
 * Return 3 and do not set the value if the value at 'noteValue' emplacement is already true.
 * Return 0 if ok.
 */
int insertNote(Cell *cell, int noteValue);

/**
 * Set the value 1 at the 'noteValue' emplacement in notes.
 * Return 1 if the cell is not modifiable.
 * Return 2 and do not set the value if 'noteValue' makes no sense.
 * Return 3 and do not set the value if the value at 'noteValue' emplacement is already false.
 * Return 0 if ok.
 */
int removeNote(Cell *cell, int noteValue);

#endif
