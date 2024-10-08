#include <cell.h>
#include <felib/bool.h>

/*
 * Define a cell in the Sudoku grid where the player has to find the value.
*/
typedef struct playableCell {
	Cell cell;
	bool[9] notes;
} PlayableCell;

/**
 * Set the value 1 at the 'noteValue' emplacement in notes.
 * Return 1 and do not set the value if 'noteValue' superior to 9.
 * Return 2 and do not set the value if the value at 'noteValue' emplacement is already equal to 1.
 * Return 0 if ok.
*/
int insertNote(PlayableCell* cell, char noteValue);

/*
 * Set the value 1 at the 'noteValue' emplacement in notes.
 * Return 1 and do not set the value if 'noteValue' superior to 9.
 * Return 2 and do not set the value if the value at 'noteValue' emplacement is already equal to 1.
 * Return 0 if ok.
*/
int removeNote(PlayableCell* cell, char noteValue);

/*
 * Insert the value 'value' in the cell 'cell'.
 * Return 2 if the value in the cell 'cell' is already defined (and still do the insertion).
 * Return 0 if ok.
*/
int insertValue(PlayableCell* cell, char value);

/*
 * Set the value to 0 in the cell 'cell'.
 * Return 2 if the value is already to 0.
 * Return 0 if ok.
*/
int removeValue(PlayableCell* cell);
