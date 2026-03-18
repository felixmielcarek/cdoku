//
// Input handler module for processing SDL events
//

#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <SDL2/SDL.h>
#include <stdlib.h>
#include <string.h>
#include "../constants/constants.h"

typedef enum {
    INPUT_NONE,
    INPUT_QUIT,
    INPUT_NUMBER,
    INPUT_ARROW_LEFT,
    INPUT_ARROW_RIGHT,
    INPUT_ARROW_UP,
    INPUT_ARROW_DOWN,
    INPUT_DELETE,
    INPUT_TOGGLE_NOTE,
    INPUT_CONFIRM,
    INPUT_CELL_CLICK,
    INPUT_NOTE_ICON_CLICK,
    INPUT_MENU_CLICK
} InputAction;

typedef struct {
    InputAction action;
    int value;      // For number inputs
    int x, y;       // For mouse clicks
} InputEvent;

/**
 * Process SDL event and return structured input.
 */
InputEvent processEvent(SDL_Event *event);

/**
 * Convert screen coordinates to grid cell coordinates.
 * Returns 0 on success, 1 if out of bounds.
 */
int getCoordonatesCell(const int x, const int y, int *column, int *row);

#endif // INPUT_HANDLER_H
