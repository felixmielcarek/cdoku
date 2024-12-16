//
// Created by felixmielcarek on 11/28/24.
//

#include "rendering.h"

int renderSelection(const GuiElements *guiElements, const Grid grid, const int cellColumn, const int cellRow) {
    int sectionColumn = cellColumn / 3, sectionRow = cellRow / 3;

    for (int col = 0; col < 9; ++col) {
        int tmpSectionCol = col / 3;
        for (int row = 0; row < 9; ++row) {
            int tmpSectionRow = row / 3;
            SDL_Color textColor = grid.cells[col][row].isModifiable ? CELLTEXTCOLOR : FIXCELLTEXTCOLOR;
            if (col == cellColumn || row == cellRow || (tmpSectionCol == sectionColumn && tmpSectionRow == sectionRow))
                renderCell(guiElements, grid.cells[col][row], col, row, textColor, LINKEDSELECTEDCELLCOLOR);
            else if (grid.cells[cellColumn][cellRow].value != 0 &&
                     grid.cells[cellColumn][cellRow].value == grid.cells[col][row].value)
                renderCell(guiElements, grid.cells[col][row], col, row, textColor, NUMBERSELECTEDCELLCOLOR);
            else
                renderCell(guiElements, grid.cells[col][row], col, row, textColor, CELLCOLOR);
        }
    }
    renderCell(guiElements, grid.cells[cellColumn][cellRow], cellColumn, cellRow, CELLTEXTCOLOR, SELECTEDCELLCOLOR);

    return 0;
}

int renderWunGrid(const GuiElements *guiElements, const Grid grid) {
    for (int col = 0; col < 9; ++col) {
        for (int row = 0; row < 9; ++row) {
            renderCellBorders(guiElements, col, row, ENDCELLBORDERCOLOR);
            renderCell(guiElements, grid.cells[col][row], col, row, ENDCELLTEXTCOLOR,
                       grid.cells[col][row].isModifiable ? WUNCELLCOLOR : ENDCELLCOLOR);
        }
    }

    for (int sectionColumn = 0; sectionColumn < 3; ++sectionColumn)
        for (int sectionRow = 0; sectionRow < 3; ++sectionRow)
            renderSectionBorders(guiElements, sectionColumn, sectionRow, ENDSECTIONBORDERCOLOR);

    return 0;
}

int renderLostGrid(const GuiElements *guiElements, const Grid grid) {
    for (int col = 0; col < 9; ++col) {
        for (int row = 0; row < 9; ++row) {
            renderCellBorders(guiElements, col, row, ENDCELLBORDERCOLOR);
            renderCell(guiElements, grid.cells[col][row], col, row, ENDCELLTEXTCOLOR,
                       grid.cells[col][row].isModifiable ? LOSTCELLCOLOR : ENDCELLCOLOR);
        }
    }

    for (int sectionColumn = 0; sectionColumn < 3; ++sectionColumn)
        for (int sectionRow = 0; sectionRow < 3; ++sectionRow)
            renderSectionBorders(guiElements, sectionColumn, sectionRow, ENDSECTIONBORDERCOLOR);

    return 0;
}

int renderNoteIcon(const GuiElements *guiElements, const int isToggled) {
    const char *iconPath = isToggled == 1 ? NOTEICONPATHTOGGLED : NOTEICONPATHNOTTOGGLED;

    SDL_Surface *loadedSurface = IMG_Load(iconPath);

    SDL_Texture *texture = SDL_CreateTextureFromSurface(guiElements->renderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);

    SDL_Rect rect = {NOTEICONX, NOTEICONY, NOTEICONSIZE, NOTEICONSIZE};
    setRanderDrawColor(guiElements->renderer, NOTEICONBG);
    SDL_RenderFillRect(guiElements->renderer, &rect);

    setRanderDrawColor(guiElements->renderer, NOTEICONBORDERCOLOR);
    for (int i = 0; i < NOTEICONBORDERSIZE; ++i) {
        SDL_Rect border = {NOTEICONX - (i + 1), NOTEICONY - (i + 1), NOTEICONSIZE + (i + 1) * 2,
                           NOTEICONSIZE + (i + 1) * 2};
        SDL_RenderDrawRect(guiElements->renderer, &border);
    }

    SDL_RenderCopy(guiElements->renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);

    SDL_RenderPresent(guiElements->renderer);
    return 0;
}

int renderGrid(const GuiElements *guiElements, const Grid grid) {

    for (int col = 0; col < 9; ++col) {
        for (int row = 0; row < 9; ++row) {
            SDL_Color textColor = grid.cells[col][row].isModifiable ? CELLTEXTCOLOR : FIXCELLTEXTCOLOR;
            renderCellBorders(guiElements, col, row, CELLBORDERCOLOR);
            renderCell(guiElements, grid.cells[col][row], col, row, textColor, CELLCOLOR);
        }
    }

    for (int sectionColumn = 0; sectionColumn < 3; ++sectionColumn)
        for (int sectionRow = 0; sectionRow < 3; ++sectionRow)
            renderSectionBorders(guiElements, sectionColumn, sectionRow, SECTIONBORDERCOLOR);

    return 0;
}

int renderMainMenu(const GuiElements *guiElements) {
    char *text = "Nouvelle partie";
    int textWidth, textHeight;

    renderBase(guiElements);

    setRanderDrawColor(guiElements->renderer, MAINMENUBGCOLOR);
    SDL_Rect rect = {MAINMENUX, MAINMENUY, MAINMENUWIDTH, MAINMENUHEIGHT};
    SDL_RenderFillRect(guiElements->renderer, &rect);

    TTF_Font *font = TTF_OpenFont(FONTNAME, FONTSIZE);
    TTF_SizeText(font, text, &textWidth, &textHeight);

    SDL_Surface *textSurface = TTF_RenderText_Blended(font, text, MAINMENUTEXTCOLOR);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(guiElements->renderer, textSurface);
    SDL_FreeSurface(textSurface);

    SDL_Rect textRect = {MAINMENUX + MAINMENUWIDTH / 2 - textWidth / 2, MAINMENUY + MAINMENUHEIGHT / 2 - textHeight / 2,
                         textWidth, textHeight};
    SDL_RenderCopy(guiElements->renderer, textTexture, NULL, &textRect);

    SDL_DestroyTexture(textTexture);
    TTF_CloseFont(font);

    return 0;
}

int renderBase(const GuiElements *guiElements) {
    setRanderDrawColor(guiElements->renderer, BGCOLOR);
    SDL_RenderClear(guiElements->renderer);

    return 0;
}
