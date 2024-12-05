//
// Created by felixmielcarek on 11/30/24.
//

#include "sectionRendering.h"

int renderSectionBorders(const GuiElements *guiElements, const int column, const int row, const SDL_Color borderColor) {
    int sectionX = GRIDX + column * SECTIONSIZE + column * SECTIONBORDERSIZE,
        sectionY = GRIDY + row * SECTIONSIZE + row * SECTIONBORDERSIZE;

    setRanderDrawColor(guiElements->renderer, borderColor);
    for (int i = 0; i < SECTIONBORDERSIZE; ++i) {
        SDL_Rect border = {sectionX - (i + 1), sectionY - (i + 1), SECTIONSIZE + (i + 1) * 2,
                           SECTIONSIZE + (i + 1) * 2};
        SDL_RenderDrawRect(guiElements->renderer, &border);
    }

    return 0;
}
