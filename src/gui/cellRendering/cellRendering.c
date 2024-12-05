//
// Created by felixmielcarek on 11/30/24.
//

#include "cellRendering.h"

int getCellCoordonates(const int column, const int row, int *x, int *y) {
    int sectionColumn = column / 3, sectionRow = row / 3;
    int columnInSection = column - sectionColumn * 3, rowInSection = row - sectionRow * 3;
    *x = GRIDX + SECTIONSIZE * sectionColumn + SECTIONBORDERSIZE * sectionColumn + CELLSIZE * columnInSection +
         CELLBORDERSIZE * columnInSection;
    *y = GRIDY + SECTIONSIZE * sectionRow + SECTIONBORDERSIZE * sectionRow + CELLSIZE * rowInSection +
         CELLBORDERSIZE * rowInSection;

    return 0;
}

int renderCellBackground(const GuiElements *guiElements, const int column, const int row, const SDL_Color color) {
    int x, y;
    getCellCoordonates(column, row, &x, &y);

    setRanderDrawColor(guiElements->renderer, color);
    SDL_Rect background = {x, y, CELLSIZE, CELLSIZE};
    SDL_RenderFillRect(guiElements->renderer, &background);
    return 0;
}

int renderCellBorders(const GuiElements *guiElements, const int column, const int row, const SDL_Color borderColor) {
    int x, y;
    getCellCoordonates(column, row, &x, &y);

    setRanderDrawColor(guiElements->renderer, borderColor);
    for (int i = 0; i < CELLBORDERSIZE; ++i) {
        SDL_Rect border = {x - (i + 1), y - (i + 1), CELLSIZE + (i + 1) * 2, CELLSIZE + (i + 1) * 2};
        SDL_RenderDrawRect(guiElements->renderer, &border);
    }

    return 0;
}

int renderCellText(const GuiElements *guiElements, const Cell cell, const int column, const int row,
                   const SDL_Color textColor) {
    char text[2];
    int textWidth, textHeight, cellX, cellY;

    text[0] = cell.value + 48;
    text[1] = 0;

    TTF_Font *font = TTF_OpenFont(FONTNAME, FONTSIZE);
    TTF_SizeText(font, text, &textWidth, &textHeight);

    SDL_Surface *textSurface = TTF_RenderText_Blended(font, text, textColor);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(guiElements->renderer, textSurface);
    SDL_FreeSurface(textSurface);

    getCellCoordonates(column, row, &cellX, &cellY);
    SDL_Rect textRect = {CELLSIZE / 2 - textWidth / 2 + cellX, CELLSIZE / 2 - textHeight / 2 + cellY, textWidth,
                         textHeight};
    SDL_RenderCopy(guiElements->renderer, textTexture, NULL, &textRect);

    SDL_DestroyTexture(textTexture);
    TTF_CloseFont(font);

    return 0;
}

int renderCell(const GuiElements *guiElements, const Cell cell, const int column, const int row,
               const SDL_Color textColor, const SDL_Color backgroundColor) {
    renderCellBackground(guiElements, column, row, backgroundColor);
    if (cell.value != 0)
        renderCellText(guiElements, cell, column, row, textColor);

    return 0;
}
