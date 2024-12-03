include variables.mk

NAME = cdoku
SUBDIRS = game gui
OBJS := $(shell find . -type f -name "*.o")
.PHONY: $(SUBDIRS) clean

all: $(NAME).out

$(NAME).out : $(NAME).o $(OBJS)
	$(CC) -o $(NAME).out $(OBJS) $(SDLFLAGS)

$(NAME).o : $(NAME).c $(SUBDIRS)
	$(CC) -c $(CFLAGS) $(NAME).c

$(SUBDIRS):
	$(MAKE) -C $@

clean:
	@for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir clean; \
	done
	rm -f $(NAME).out *.o