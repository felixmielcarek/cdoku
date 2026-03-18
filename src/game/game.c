//
// Created by felixmielcarek on 11/26/24.
//

#include "game.h"

int isGameFinished(const Grid grid) {
    int isGridCorrect = 1;

    for (int col = 0; col < 9; ++col) {
        for (int row = 0; row < 9; ++row) {
            if (grid.cells[col][row].value == 0)
                return 1;
            if (grid.cells[col][row].value != grid.solution[col][row])
                isGridCorrect = 0;
        }
    }
    if (isGridCorrect != 1)
        return 2;
    return 0;
}

int getNewGrid(Grid *result) {
    char *apiData = NULL;

    apiRequest(&apiData);
    parseJsonData(result, apiData);
    free(apiData);

    return 0;
}
