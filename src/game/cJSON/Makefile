include ../../variables.mk

NAME = cJSON

all : $(NAME).o

$(NAME).o : $(NAME).c
	$(CC) -c $(CFLAGS) $(NAME).c

clean :
	rm -f $(NAME).out *.o