#ifndef _MAP_INCLUDED_
#define _MAP_INCLUDED_

#include <SDL2/SDL.h>

#define MAP_WIDTH 25
#define MAP_HEIGHT 13

class Map {
 public:
  Map(SDL_Surface *surface) : surface(surface) {}

	bool render(const char *map);
	
 private:
 	int width;
	int height;
	SDL_Surface *surface;
};

#endif  // _MAP_INCLUDED_

