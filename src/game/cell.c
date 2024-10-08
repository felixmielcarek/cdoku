#include <cell.h>

int insertValue(Cell* cell, char value) {
	int result = cell->value == 0 ? 0 : 2 ;
	cell->value = value;
	return result;
}
