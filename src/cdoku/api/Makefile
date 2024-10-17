NAME = api
CC = gcc
CFLAGS = -Wall -g -std=c99 -pedantic 

all : $(NAME).out
	
$(NAME).out : $(NAME).o
	$(CC) -o $(NAME).out $(NAME).o

$(NAME).o : $(NAME).c
	$(CC) -c $(CFLAGS) $(NAME).c 

clean :
	rm -f $(NAME) *.o
