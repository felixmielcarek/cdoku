//
// Input handler module for processing SDL events
//

#include "input_handler.h"

int getCoordonatesCell(const int x, const int y, int *column, int *row) {
    const int noBorderX = x - GRIDX - SECTIONBORDERSIZE, // removes the outside left border of the grid
            noBorderY = y - GRIDY - SECTIONBORDERSIZE; // removes the outside top border of the grid

    if (noBorderX < 0 || noBorderY < 0 || noBorderX > 3 * SECTIONSIZE + 2 * SECTIONBORDERSIZE ||
        noBorderY > 3 * SECTIONSIZE + 2 * SECTIONBORDERSIZE) {
        *column = -1;
        *row = -1;
        return 1;
    }

    *column = noBorderX / (CELLSIZE + CELLBORDERSIZE);
    *row = noBorderY / (CELLSIZE + CELLBORDERSIZE);

    return 0;
}

InputEvent processEvent(SDL_Event *event) {
    InputEvent input = {INPUT_NONE, 0, 0, 0};

    switch (event->type) {
        case SDL_QUIT:
            input.action = INPUT_QUIT;
            break;

        case SDL_KEYDOWN: {
            const char *keyName = SDL_GetKeyName(event->key.keysym.sym);
            int value = atoi(keyName);
            
            if (value >= 1 && value <= 9) {
                input.action = INPUT_NUMBER;
                input.value = value;
            } else if (strcmp(keyName, "Left") == 0) {
                input.action = INPUT_ARROW_LEFT;
            } else if (strcmp(keyName, "Right") == 0) {
                input.action = INPUT_ARROW_RIGHT;
            } else if (strcmp(keyName, "Up") == 0) {
                input.action = INPUT_ARROW_UP;
            } else if (strcmp(keyName, "Down") == 0) {
                input.action = INPUT_ARROW_DOWN;
            } else if (strcmp(keyName, "Backspace") == 0 || strcmp(keyName, "Delete") == 0) {
                input.action = INPUT_DELETE;
            } else if (strcmp(keyName, "N") == 0) {
                input.action = INPUT_TOGGLE_NOTE;
            } else if (strcmp(keyName, "Return") == 0) {
                input.action = INPUT_CONFIRM;
            }
            break;
        }

        case SDL_MOUSEBUTTONDOWN:
            if (event->button.button == 1) { // Left click only
                input.x = event->button.x;
                input.y = event->button.y;

                // Check if note icon clicked
                if (input.x >= NOTEICONX && input.x <= NOTEICONX + NOTEICONSIZE &&
                    input.y >= NOTEICONY && input.y <= NOTEICONY + NOTEICONSIZE) {
                    input.action = INPUT_NOTE_ICON_CLICK;
                }
                // Check if main menu button clicked
                else if (input.x >= MAINMENUX && input.x <= MAINMENUX + MAINMENUWIDTH &&
                         input.y >= MAINMENUY && input.y <= MAINMENUY + MAINMENUHEIGHT) {
                    input.action = INPUT_MENU_CLICK;
                }
                // Otherwise it's a cell click
                else {
                    input.action = INPUT_CELL_CLICK;
                }
            }
            break;

        default:
            break;
    }

    return input;
}
