CC = g++
CFLAGS = -Wall -Wextra -lSDL2
CFLAGS_DEBUG = -g

FILES = main.cc

all:
	$(CC) $(FILES) -o main $(CFLAGS)

debug:
	$(CC) $(FILES) -o main $(CFLAGS) $(CFLAGS_DEBUG)

run: all
	./main

clean:
	rm -rf main


