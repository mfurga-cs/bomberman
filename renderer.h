#pragma once

#include <SDL2/SDL.h>

#define TILE_WIDTH 48
#define TILE_HEIGHT 48

class Renderer {
 public:
  Renderer() {}

  void set_window_surface(SDL_Surface *window_surface);

  int load_tiles(const char *fname);

  void render_tile(int sx, int sy, int dx, int dy) const;

 private:
  SDL_Surface *tiles_;
  SDL_Surface *window_surface_;
};
