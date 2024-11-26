#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>	// to render text with SDL
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "constants.h"

typedef struct guiElements {
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* textTexture;
} GuiElements;

int cleanExit(int result, GuiElements* guiElements) {
	if(guiElements->window != NULL) 
		SDL_DestroyWindow(guiElements->window);
	if(guiElements->renderer != NULL) 
		SDL_DestroyRenderer(guiElements->renderer);

	TTF_Quit();
	SDL_Quit();
	return result;
}

int exitOnError(int result, GuiElements* guiElements, char* context) {
	fprintf(stderr, "Error: %s.\n",context);
	return cleanExit(result, guiElements);
}

int exitOnTTFError(int result, GuiElements* guiElements, char* context) {
	fprintf(stderr, "Error TTF [%s]: %s", context, TTF_GetError());
	return cleanExit(result, guiElements);
}

int exitOnSDLError(int result, GuiElements* guiElements, char* context) {
	fprintf(stderr, "Error SDL [%s]: %s", context, SDL_GetError());	
	return cleanExit(result, guiElements);
}

int setRanderDrawColor(SDL_Renderer* renderer, SDL_Color color) {
	return SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 
			color.a);
}

int renderEmptyGrid(GuiElements* guiElements) {
	bool isLastSectionGray = false;

	// region: Background
	setRanderDrawColor(guiElements->renderer, BGCOLOR);
	SDL_RenderClear(guiElements->renderer);
	// endregion : Background
	

	// region : Grid
	for(int sectionRow=0 ; sectionRow<3 ; ++sectionRow) {
		int sectionX = sectionRow * SECTIONSIZE + GRIDX;
		for(int sectionColumn=0 ; sectionColumn<3 ; ++sectionColumn) {
			int sectionY = sectionColumn * SECTIONSIZE + GRIDY;

			// region : Section
			setRanderDrawColor(guiElements->renderer, 
					isLastSectionGray ? WHITE : GRAY1);

			SDL_Rect section = { 
				sectionX, sectionY, SECTIONSIZE, SECTIONSIZE
			};

			SDL_RenderFillRect(guiElements->renderer, &section);

			// To alternate section colors
			isLastSectionGray = !isLastSectionGray; 

			for(int cellRow=0 ; cellRow<3 ; ++cellRow) {
				for(int cellColumn=0 ; cellColumn<3 ;
						++cellColumn) {
					// region : Cell
					setRanderDrawColor( 
							guiElements->renderer, 
							GRAY2);
					SDL_Rect cell = { 
						cellRow*CELLSIZE + sectionX,
						cellColumn*CELLSIZE + sectionY,
						CELLSIZE, CELLSIZE
					};

					SDL_RenderDrawRect( 
							guiElements->renderer,
							&cell);
					// endregion : Cell
				}
			}
			// endregion : Section
		}
	}
	// endregion : Grid
	
    SDL_RenderPresent(guiElements->renderer);

	return 0;
}

int renderNumberInCell(GuiElements* guiElements, char* text, int row, int column) {
	int textWidth, textHeight;

	if(TTF_Init() == -1)
		return exitOnTTFError(EXIT_FAILURE, guiElements, "SDL TTF init");

	TTF_Font* font = TTF_OpenFont(FONTNAME, FONTSIZE);
	TTF_SizeText(font, text, &textWidth, &textHeight);

	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, BLACK);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(guiElements->renderer, textSurface);
	SDL_FreeSurface(textSurface);

	SDL_Rect textRect = {
		GRIDX + (CELLSIZE/2) - (textWidth/2) + (CELLSIZE*row),
		GRIDY + (CELLSIZE/2) - (textHeight/2) + (CELLSIZE*column), textWidth, textHeight
	};
	SDL_RenderCopy(guiElements->renderer, textTexture, NULL, &textRect);
	SDL_RenderPresent(guiElements->renderer);

	SDL_DestroyTexture(textTexture);
	TTF_CloseFont(font);

	return 0;
}

int main(int argc, char *argv[]) {
	GuiElements guiElements;

	if(SDL_Init(SDL_INIT_VIDEO) != 0) 
		return exitOnSDLError(EXIT_FAILURE, &guiElements, "SDL init");

	guiElements.window = SDL_CreateWindow("Cdoku", 	SDL_WINDOWPOS_CENTERED, 
			SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
	if(guiElements.window == NULL) 
		return exitOnSDLError(EXIT_FAILURE, &guiElements,
				"window creation");

	guiElements.renderer = SDL_CreateRenderer(guiElements.window, -1, 
			SDL_RENDERER_ACCELERATED);
	if(guiElements.renderer == NULL)
		return exitOnSDLError(EXIT_FAILURE, &guiElements,
				"renderer creation");

	renderEmptyGrid(&guiElements);
	renderNumberInCell(&guiElements, "1", 0, 0);
	renderNumberInCell(&guiElements, "2", 1, 0);

	SDL_Delay(3000);

	return cleanExit(EXIT_SUCCESS, &guiElements);
}
