NAME = gui
CC = gcc
CFLAGS = -Wall -g -std=c99 -pedantic
SDLFLAGS = `sdl2-config --cflags --libs` -lSDL2_ttf

all : $(NAME).out

$(NAME).out : $(NAME).o
	$(CC) -o $(NAME).out $(NAME).o $(SDLFLAGS)

$(NAME).o : $(NAME).c
	$(CC) -c $(CFLAGS) $(NAME).c $(SDLFLAGS)

clean :
	rm -f $(NAME) *.o
