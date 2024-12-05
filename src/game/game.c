//
// Created by felixmielcarek on 11/26/24.
//

#include "game.h"

int isGameFinished(const Grid grid) {
    for (int col = 0; col < 9; ++col) {
        for (int row = 0; row < 9; ++row) {
            if(grid.cells[col][row].value == 0) return 1;
            //if(grid.cells[col][row].value != grid.solution[col][row]) return 2;
        }
    }
    return 0;
}

void insertNewCell(Grid* grid, const int column, const int row, const int value) {
    Cell newCell;
    newCell.isModifiable = value == 0;
    for(int i=0 ; i<9 ; ++i) newCell.notes[i] = false;
    newCell.value = value;

    grid->cells[column][row] = newCell;
}

void insertNewCellSolution(Grid* grid, const int column, const int row, const int value) {
    grid->solution[column][row] = value;
}

int parseJsonGrid(Grid* result, char* json, void (*insertJsonValue)(Grid*, const int, const int, const int)){
    int rowIndex=0, columnIndex=0;

    if(!json)
        return 1;

    cJSON *gridArray = cJSON_Parse(json);
    if (!gridArray)
        return 2;

    if (!cJSON_IsArray(gridArray)) {
        cJSON_Delete(gridArray);
        return 2;
    }

    if(cJSON_GetArraySize(gridArray) != 9) {
        cJSON_Delete(gridArray);
        return 2;
    }

    cJSON *row = NULL;
    cJSON_ArrayForEach(row, gridArray) {
        if (!cJSON_IsArray(row)) {
            cJSON_Delete(gridArray);
            result = NULL;
            return 2;
        }

        if (cJSON_GetArraySize(row) != 9) {
            cJSON_Delete(gridArray);
            result = NULL;
            return 2;
        }

        cJSON *value = NULL;
        cJSON_ArrayForEach(value, row) {
            if (!cJSON_IsNumber(value)) {
                cJSON_Delete(gridArray);
                result = NULL;
                return 2;
            }

            (*insertJsonValue)(result, columnIndex, rowIndex, value->valueint);

            columnIndex = columnIndex+1;
        }
        columnIndex = 0;

        rowIndex = rowIndex+1;
    }

    cJSON_Delete(gridArray);
    return 0;
}


int getNewGrid(Grid* result) {
    char* gridJson = "[[5,0,0,3,7,0,0,1,8],[0,0,0,6,1,0,0,5,9],[7,0,6,0,8,9,3,2,4],[0,0,0,0,5,8,1,0,0],[0,0,9,0,6,0,5,4,2],[0,4,0,0,0,0,8,0,6],[0,0,0,0,9,0,0,3,0],[4,0,0,1,0,6,0,0,5],[9,5,3,0,4,0,2,0,1]]";
    char* solutionJson = "[[5,9,4,3,7,2,6,1,8],[2,3,8,6,1,4,7,5,9],[7,1,6,5,8,9,3,2,4],[6,2,7,4,5,8,1,9,3],[1,8,9,7,6,3,5,4,2],[3,4,5,9,2,1,8,7,6],[8,6,1,2,9,5,4,3,7],[4,7,2,1,3,6,9,8,5],[9,5,3,8,4,7,2,6,1]]";

    parseJsonGrid(result, gridJson, insertNewCell);
    parseJsonGrid(result, solutionJson, insertNewCellSolution);

    return 0;
}