#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct guiElements {
	SDL_Window* window;
	SDL_Renderer* renderer;
} GuiElements;

int cleanExit(int result, GuiElements* guiElements) {
	if(guiElements->window != NULL) 
		SDL_DestroyWindow(guiElements->window);
	if(guiElements->renderer != NULL) 
		SDL_DestroyRenderer(guiElements->renderer);
	
	SDL_Quit();
	return result;
}

int exitOnError(int result, GuiElements* guiElements, char* context) {
	fprintf(stderr, "Error: %s.\n",context);
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
	SDL_Color bgColor	= {0  , 193, 255, 255};
	SDL_Color white		= {255, 255, 255, 255};
	SDL_Color gray1		= {215, 219, 221, 255};
	SDL_Color gray2		= {121, 125, 127, 255};
	bool isLastSectionGray = false;
	int sectionSize = 120;
	int cellSize = sectionSize/3;
	int gridX = 100;
	int gridY = 100;

	// region: Background
	setRanderDrawColor(guiElements->renderer, bgColor);
	SDL_RenderClear(guiElements->renderer);
	// endregion : Background
	

	// region : Grid
	for(int sectionRow=0 ; sectionRow<3 ; ++sectionRow) {
		int sectionX = sectionRow * sectionSize + gridX;
		for(int sectionColumn=0 ; sectionColumn<3 ; ++sectionColumn) {
			int sectionY = sectionColumn * sectionSize + gridY;

			// region : Section
			setRanderDrawColor(guiElements->renderer, 
					isLastSectionGray ? white : gray1);

			SDL_Rect section = { 
				sectionX, sectionY, sectionSize, sectionSize 
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
							gray2);
					SDL_Rect cell = { 
						cellRow*cellSize + sectionX,
						cellColumn*cellSize + sectionY,
						cellSize, cellSize 
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

int main(int argc, char *argv[]) {
	GuiElements guiElements;

	if(SDL_Init(SDL_INIT_VIDEO) != 0) 
		return exitOnSDLError(EXIT_FAILURE, &guiElements, "init");

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

	SDL_Delay(10000);

	return cleanExit(EXIT_SUCCESS, &guiElements);
}
