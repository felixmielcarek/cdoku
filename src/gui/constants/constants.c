#include "constants.h"

const SDL_Color WHITE = {255, 255, 255, 255};
const SDL_Color GRAY1 = {133, 146, 158, 255};
const SDL_Color GRAY2 = {121, 125, 127, 255};
const SDL_Color BLACK = {0, 0, 0, 0};
const SDL_Color BLUE1 = {174, 214, 241, 255};
const SDL_Color BLUE2 = {133, 193, 233, 255};
const SDL_Color BLUE3 = {93, 173, 226, 255};

const SDL_Color BGCOLOR = GRAY2;
const SDL_Color SELECTEDCELLCOLOR = BLUE3;
const SDL_Color NUMBERSELECTEDCELLCOLOR = BLUE2;
const SDL_Color LINKEDSELECTEDCELLCOLOR = BLUE1;
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
