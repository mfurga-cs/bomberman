#pragma once

#include <SDL2/SDL.h>

#define TILE_WIDTH 48
#define TILE_HEIGHT 48

class Renderer {
 public:
  Renderer() {}

  int init(SDL_Window *window);

  void update() const;

  int load_tiles(const char *fname);

  void render_tile(int sx, int sy, int dx, int dy) const;

  void render_tile(int sx, int sy, int dx, int dy, double angle) const;

 private:
  // SDL_Surface *tiles_;
  SDL_Surface *window_surface_;

  SDL_Renderer *renderer_;
  SDL_Texture *tiles_;
};
