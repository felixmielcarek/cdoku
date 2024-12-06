//
// Created by felixmielcarek on 11/26/24.
//

#include "game.h"

int isGameFinished(const Grid grid) {
    for (int col = 0; col < 9; ++col) {
        for (int row = 0; row < 9; ++row) {
            if (grid.cells[col][row].value == 0)
                return 1;
            if (grid.cells[col][row].value != grid.solution[col][row])
                return 2;
        }
    }
    return 0;
}

void insertNewCell(Grid *grid, const int column, const int row, const int value) {
    Cell newCell;
    newCell.isModifiable = value == 0;
    for (int i = 0; i < 9; ++i)
        newCell.notes[i] = false;
    newCell.value = value;

    grid->cells[column][row] = newCell;
}

void insertNewCellSolution(Grid *grid, const int column, const int row, const int value) {
    grid->solution[column][row] = value;
}

int parseJsonGrid(Grid *result, cJSON *json, void (*insertJsonValue)(Grid *, const int, const int, const int)) {
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

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t totalSize = size * nmemb;
    ApiResponse *res = (ApiResponse *) userp;

    char *ptr = realloc(res->data, res->size + totalSize + 1); // +1 for the null terminator
    if (ptr == NULL) {
        fprintf(stderr, "Not enough memory (realloc failed)\n");
        return 0; // Signal an error to libcurl
    }

    res->data = ptr;
    memcpy(&res->data[res->size], contents, totalSize);
    res->size += totalSize;
    res->data[res->size] = '\0';

    return totalSize;
}

int apiRequest(char **result) {
    ApiResponse apiResponse = {NULL, 0};
    CURL *curl = curl_easy_init();

    if (curl) {
        CURLcode apiResCode;

        curl_easy_setopt(curl, CURLOPT_URL, "https://sudoku-api.vercel.app/api/dosuku");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *) &apiResponse);

        apiResCode = curl_easy_perform(curl);

        if (apiResCode != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(apiResCode));
        else
            *result = apiResponse.data;

        curl_easy_cleanup(curl);
    }


    return 0;
}

int getNewGrid(Grid *result) {
    char *apiData = NULL;

    apiRequest(&apiData);
    parseJsonData(result, apiData);
    free(apiData);

    return 0;
}
