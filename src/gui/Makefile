include ../variables.mk

NAME = gui
SUBDIRS = constants common rendering cellRendering sectionRendering
.PHONY: $(SUBDIRS) clean

all: $(NAME).o

$(NAME).o : $(NAME).c $(SUBDIRS)
	$(CC) -c $(CFLAGS) $(NAME).c

$(SUBDIRS):
	$(MAKE) -C $@

clean:
	@for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir clean; \
	done
	rm -f $(NAME).out *.o