CC = gcc
CFLAGS = -Wall -Wextra # -std=c99

debug:
	$(CC) -o curser main.c $(CFLAGS) -g

build:
	$(CC) -o curser main.c $(CFLAGS) -O3

clean:
	rm curser
