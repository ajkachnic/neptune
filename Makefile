CC=gcc
CFLAGS=-I. -Wall -std=c99 -ledit -lm
DEPS = main.h common.h
OBJ = main.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
