CC=gcc
CFLAGS=-Ofast -lm

all: cliff.c
	$(CC) $(CFLAGS) -o cliff cliff.c
