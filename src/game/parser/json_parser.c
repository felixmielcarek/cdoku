//
// JSON parser module for converting API responses to Grid structures
//

#include "json_parser.h"

static void insertNewCell(Grid *grid, const int column, const int row, const int value) {
    Cell newCell;
    newCell.isModifiable = value == 0;
    for (int i = 0; i < 9; ++i)
        newCell.notes[i] = false;
    newCell.value = value;

    grid->cells[column][row] = newCell;
}

static void insertNewCellSolution(Grid *grid, const int column, const int row, const int value) {
    grid->solution[column][row] = value;
}

static int parseJsonGrid(Grid *result, cJSON *json, void (*insertJsonValue)(Grid *, const int, const int, const int)) {
    int rowIndex = 0, columnIndex = 0;

    if (cJSON_GetArraySize(json) != 9) {
        cJSON_Delete(json);
        return 2;
    }

    cJSON *row = NULL;
    cJSON_ArrayForEach(row, json) {
        if (!cJSON_IsArray(row)) {
            cJSON_Delete(json);
            result = NULL;
            return 2;
        }
        if (cJSON_GetArraySize(row) != 9) {
            cJSON_Delete(json);
            result = NULL;
            return 2;
        }

        cJSON *value = NULL;
        cJSON_ArrayForEach(value, row) {
            if (!cJSON_IsNumber(value)) {
                cJSON_Delete(json);
                result = NULL;
                return 2;
            }

            (*insertJsonValue)(result, columnIndex, rowIndex, value->valueint);

            columnIndex = columnIndex + 1;
        }
        columnIndex = 0;

        rowIndex = rowIndex + 1;
    }
    return 0;
}

int parseJsonData(Grid *result, char *jsonData) {
    cJSON *json = cJSON_Parse(jsonData);
    if (json == NULL) {
        printf("Error parsing JSON\n");
        return 1;
    }

    cJSON *newboard = cJSON_GetObjectItem(json, "newboard");
    if (newboard == NULL) {
        cJSON_Delete(newboard);
        return 2;
    }

    cJSON *grids = cJSON_GetObjectItem(newboard, "grids");
    if (grids == NULL || !cJSON_IsArray(grids)) {
        cJSON_Delete(grids);
        return 2;
    }

    cJSON *first_grid = cJSON_GetArrayItem(grids, 0);
    if (first_grid == NULL) {
        cJSON_Delete(first_grid);
        return 2;
    }

    cJSON *value = cJSON_GetObjectItem(first_grid, "value");
    if (value == NULL || !cJSON_IsArray(value)) {
        cJSON_Delete(value);
        return 2;
    }
    parseJsonGrid(result, value, insertNewCell);

    cJSON *solution = cJSON_GetObjectItem(first_grid, "solution");
    if (solution == NULL || !cJSON_IsArray(solution)) {
        cJSON_Delete(solution);
        return 2;
    }
    parseJsonGrid(result, solution, insertNewCellSolution);

    return 0;
}
