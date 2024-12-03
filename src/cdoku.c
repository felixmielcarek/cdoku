#include <stdio.h>
#include "gui/gui.h"
#include "game/game.h"

int main(int argc, char** argv) {
    Grid grid;
    int res = getNewGrid(&grid);

    for(int i=0; i<9; ++i) {
        for(int y=0; y<9; ++y)
            fprintf(stderr,"%d ",grid.cells[i][y].value);
        fprintf(stderr,"\n");
    }

    runGui(grid);

    return res;
}