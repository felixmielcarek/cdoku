/*
 * Define a cell in the Sudoku grid.
 * The value of the cell is 0 by default.
*/
typedef struct cell {
        char value=0;
} Cell;

/*
 * Insert the value 'value' in the cell 'cell'.
 * Return 2 if the value in the cell 'cell' is already defined (and still do the insertion).
 * Return 0 if ok.
*/
int insertValue(Cell* cell, char value);
