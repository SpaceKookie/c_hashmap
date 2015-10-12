HEADERS = hash.h hashmap.h
OBJ = hash.o hashmap.o main.o
CC=gcc
CFLAGS=-O2

default: test

%.o: %.c $(HEADERS)
    $(CC) -c -o $@ $< $(CFLAGS)

test: $(OBJ)
    gcc $(OBJ) -o c_hashmap

clean:
    -rm -f $(OBJ)
    -rm -f c_hashmap
