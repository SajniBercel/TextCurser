CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -D_POSIX_C_SOURCE=200809L

debug:
	$(CC) -o curser main.c $(CFLAGS) -g

build:
	$(CC) -o curser main.c $(CFLAGS) -O3

clean:
	rm curser
