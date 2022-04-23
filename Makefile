CC = g++
CFLAGS = -Wall -Wextra -lSDL2 -lSDL2_ttf

SRCS = objects/player.cc \
			 objects/bomb.cc \
			 objects/enemy.cc \
			 scenes/play.cc \
			 scenes/game_over.cc \
			 renderer.cc \
			 map.cc \
			 main.cc

all:
	$(CC) $(SRCS) -o main $(CFLAGS)

run: all
	./main

clean:
	rm -rf main


