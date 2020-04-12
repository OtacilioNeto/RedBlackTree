CFLAGS+=-Wall -O2

OBJ=rb_tree.o

.PHONY: all clean

all: $(OBJ)

rb_tree.o: rb_tree.c rb_tree.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJ)