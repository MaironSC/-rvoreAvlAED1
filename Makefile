CC=gcc

CFLAGS=-Wall -Wextra -Werror -O0 -g -std=c11 -I..

.PHONY: all clean run

all: run

arvore.o: arvore.c

fila.o: fila.c


test: arvore.o test.c
	$(CC) $(CFLAGS) fila.c test.c arvore.c -o test -lm

run: test
	./test



clean:
	rm -f *.o test