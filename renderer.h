#pragma once

#include "config.h"
#include <SDL2/SDL.h>

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
