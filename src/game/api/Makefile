# Variables

include variables.mk

NAME = api
OBJS = $(NAME).o

# Steps

all : $(NAME).out

## Link object files

$(NAME).out : $(OBJS)
	$(CC) -o $(NAME).out $(OBJS)

## Compile

$(NAME).o : $(NAME).c 
	$(CC) -c $(CFLAGS) $(NAME).c

# Clean

clean :
	rm -f $(NAME).out *.o
