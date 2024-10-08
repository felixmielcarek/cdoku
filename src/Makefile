CC = gcc
CFLAGS = -Wall -g main.c -std=c99 -pedantic 

all : cdoku.out
	
cdoku.out : main.o
	$(CC) -o cdoku.out main.o

main.o : main.c
	$(CC) -c $(CFLAGS) main.c

clean :
	rm -f cdoku *.o
