#include <playableCell.h>

int insertNote(PlayableCell* cell, int noteValue) {
	if(noteValue<9) return 1;
	if(cell->notes[noteValue] == TRUE) return 2;
	cell->notes[notesValue] = FALSE;	
	return 0;	
}

int removeNote(PlayableCell* cell, int noteValue) {
	
	return 0;	
}

int insertValue(PlayableCell* cell, int value) {

	return 0;	
}

int removeValue(PlayableCell* cell) {

	return 0;	
}
