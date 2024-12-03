#include "constants.h"

const SDL_Color WHITE = {255, 255, 255, 255};
const SDL_Color GRAY1 = {215, 219, 221, 255};
const SDL_Color GRAY2 = {121, 125, 127, 255};
const SDL_Color BLACK = {0, 0, 0, 0};
const SDL_Color BLUE = {0, 193, 255, 255};

const SDL_Color BGCOLOR = BLUE;
const SDL_Color SELECTEDCELLCOLOR = BLUE;
const SDL_Color CELLCOLOR = WHITE;

const int CELLSIZE = 40;
const int CELLBORDERSIZE = 1;
const SDL_Color CELLBORDERCOLOR = GRAY1;

const int SECTIONSIZE = CELLSIZE * 3 + CELLBORDERSIZE * 2;
const int SECTIONBORDERSIZE = 2;
const SDL_Color SECTIONBORDERCOLOR = BLACK;

const int GRIDX = 100;
const int GRIDY = 100;

const char *FONTNAME = "gui/fonts/Poppins-Regular.ttf";
const int FONTSIZE = 34;
const SDL_Color FIXCELLTEXTCOLOR = BLACK;
const SDL_Color CELLTEXTCOLOR = BLACK;
