CC=gcc
CFLAGS=-I. -Wall -std=c99 -ledit -lm -g
DEPS = main.h common.h value.h parse.h
OBJ = main.o value.o parse.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
