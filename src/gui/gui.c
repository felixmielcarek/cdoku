#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>

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

int exitOnError(int result, GuiElements* guiElements, char* message) {
	fprintf(stderr, "Error: %s.\n",message);
	return cleanExit(result, guiElements);
}

int exitOnSDLError(int result, GuiElements* guiElements, char* step) {
	fprintf(stderr, "Error SDL [%s]: %s", step, SDL_GetError());	
	return cleanExit(result, guiElements);
}

int renderEmptyGrid(GuiElements* guiElements) {
	SDL_Color bgColor = {0, 193, 255, 255};
	SDL_Color white = {255, 255, 255, 255};

	// region: Background
	if(SDL_SetRenderDrawColor(guiElements->renderer, bgColor.r, bgColor.g, 
				bgColor.b, bgColor.a) != 0)
		return exitOnSDLError(EXIT_FAILURE, guiElements, 
				"background color creation");
	if(SDL_RenderClear(guiElements->renderer) != 0)
		return exitOnSDLError(EXIT_FAILURE, guiElements, 
				"render clear");
	// endregion
	
	if(SDL_SetRenderDrawColor(guiElements->renderer, white.r, white.g, 
				white.b, white.a) != 0)
		return exitOnSDLError(EXIT_FAILURE, guiElements,
				"background color creation");
	SDL_Rect rect = {100, 100, 100, 100};
	SDL_RenderFillRect(guiElements->renderer, &rect);

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

	SDL_Delay(3000);

	return cleanExit(EXIT_SUCCESS, &guiElements);
}
