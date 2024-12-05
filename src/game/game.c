//
// Created by felixmielcarek on 11/26/24.
//

#include "game.h"

int getNewGrid(Grid* result) {
    int rowIndex=0, columnIndex=0;
    char* gridJson = "[[0,7,4,0,6,0,0,0,0], [0,0,0,0,8,0,0,0,0], [6,8,0,0,0,0,2,0,0], [1,0,5,0,0,7,0,9,0], [0,9,0,0,0,1,0,0,0], [0,0,0,0,0,0,5,0,0], [0,4,0,0,0,8,0,0,1], [0,0,0,0,0,0,0,7,0], [8,1,6,0,0,0,0,0,5]]";

    if(!gridJson)
        return 1;

    cJSON *gridArray = cJSON_Parse(gridJson);
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

            Cell newCell;
            newCell.isModifiable = value->valueint == 0;
            for(int i=0 ; i<9 ; ++i) newCell.notes[i] = false;
            newCell.value = value->valueint;

            result->cells[rowIndex][columnIndex] = newCell;

            columnIndex = columnIndex+1;
        }
        columnIndex = 0;

        rowIndex = rowIndex+1;
    }

    cJSON_Delete(gridArray);
    return 0;
}