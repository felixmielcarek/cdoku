#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <SDL2/SDL.h>

extern const SDL_Color BGCOLOR;
extern const SDL_Color SELECTEDCELLCOLOR;
extern const SDL_Color NUMBERSELECTEDCELLCOLOR;
extern const SDL_Color LINKEDSELECTEDCELLCOLOR;
extern const SDL_Color CELLCOLOR;
extern const SDL_Color ENDCELLCOLOR;
extern const SDL_Color WUNCELLCOLOR;
extern const SDL_Color LOSTCELLCOLOR;

extern const int WINDOWWIDTH;
extern const int WINDOWHEIGHT;

extern const int CELLSIZE;
extern const int CELLBORDERSIZE;
extern const SDL_Color CELLBORDERCOLOR;
extern const SDL_Color ENDCELLBORDERCOLOR;

extern const int SECTIONSIZE;
extern const int SECTIONBORDERSIZE;
extern const SDL_Color SECTIONBORDERCOLOR;
extern const SDL_Color ENDSECTIONBORDERCOLOR;

extern const int GRIDSIZE;

extern const int GRIDX;
extern const int GRIDY;

extern const int MAINMENUX;
extern const int MAINMENUY;
extern const int MAINMENUWIDTH;
extern const int MAINMENUHEIGHT;
extern const SDL_Color MAINMENUBGCOLOR;
extern const SDL_Color MAINMENUTEXTCOLOR;

extern const char *FONTNAME;
extern const int FONTSIZE;
extern const int NOTEFONTSIZE;
extern const SDL_Color FIXCELLTEXTCOLOR;
extern const SDL_Color CELLTEXTCOLOR;
extern const SDL_Color ENDCELLTEXTCOLOR;
extern const SDL_Color NOTETEXTCOLOR;
#endif
