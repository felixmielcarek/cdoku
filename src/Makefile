include variables.mk

NAME = cdoku
SRCS =$(shell find . -type f -name "*.c")	# find every C file in subfolders
OBJS = $(SRCS:.c=.o)	# copy C files names after changing the file extensions

all: $(NAME).out

$(NAME).out: $(OBJS)	# requires every C files to be compiled
	$(CC) -o $@ $(OBJS) $(SDLFLAGS) $(CURLFLAGS)

# handle a compilation of a C file
%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@
# '$<' refer to the target, here '%.o'
# '$@' refer to the requirement, here '%.c'

clean:
	rm -f $(NAME).out $(OBJS)