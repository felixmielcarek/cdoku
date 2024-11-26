#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <SDL2/SDL.h>

const SDL_Color BGCOLOR	= {0  , 193, 255, 255};
const SDL_Color WHITE	= {255, 255, 255, 255};
const SDL_Color GRAY1	= {215, 219, 221, 255};
const SDL_Color GRAY2	= {121, 125, 127, 255};
const SDL_Color BLACK	= {0, 0, 0, 0};

const int SECTIONSIZE = 120;
const int CELLSIZE = SECTIONSIZE/3;
const int GRIDX = 100;
const int GRIDY = 100;

const char* FONTNAME = "fonts/Poppins-Regular.ttf";
const int FONTSIZE = 34;
#endif