CC = g++
CFLAGS = -Wall -Wextra -lSDL2 -lSDL2_ttf
CFLAGS_DEBUG = -g

FILES = objects/player.cc objects/bomb.cc scenes/play.cc renderer.cc map.cc main.cc

all:
	$(CC) $(FILES) -o main $(CFLAGS)

debug:
	$(CC) $(FILES) -o main $(CFLAGS) $(CFLAGS_DEBUG)

run: all
	./main

clean:
	rm -rf main


