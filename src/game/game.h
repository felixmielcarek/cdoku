//
// Created by felixmielcarek on 11/26/24.
//

#ifndef GAME_H
#define GAME_H

#include "rules/grid.h"
#include "cJSON/cJSON.h"
#include <stdio.h>

/**
* Recover new sudoku grid from public REST API, parse the recovered JSON and add the soduko grid in the result structure.
* Return 1 if the API request failed and 2 if the parsing failed.
* Return 0 if ok.
*/
int getNewGrid(Grid* result);

#endif //GAME_H
