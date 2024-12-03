CC = gcc
CFLAGS = -Wall -g -std=c99 -pedantic
SDLFLAGS = `sdl2-config --cflags --libs` -lSDL2_ttf