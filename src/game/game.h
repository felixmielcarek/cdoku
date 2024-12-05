//
// Created by felixmielcarek on 11/26/24.
//

#ifndef GAME_H
#define GAME_H

#include "rules/grid.h"
#include "cJSON/cJSON.h"
#include <stdio.h>

/**
* Check if the grid is fully filled.
* Return 1 if the grid is not fully filled.
* Return 2 if the grid is fully filled but if it does not match the solution.
* Return 0 if the game is finished.
*/
int isGameFinished(const Grid grid);

/**
* Recover new sudoku grid from public REST API, parse the recovered JSON and add the soduko grid in the result structure.
* Return 1 if the API request failed and 2 if the parsing failed.
* Return 0 if ok.
*/
int getNewGrid(Grid* result);

#endif //GAME_H
