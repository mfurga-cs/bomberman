#include "renderer.h"

void Renderer::set_window_surface(SDL_Surface *window_surface) {
  window_surface_ = window_surface;
}

int Renderer::load_tiles(const char *fname) {
  tiles_ = SDL_LoadBMP(fname);
  if (tiles_ == NULL) {
    puts("SDL_LoadBMP failed");
    return 1;
  }
  return 0;
}

void Renderer::render_tile(int sx, int sy, int dx, int dy) const {
  SDL_Rect src = { .x = sx, .y = sy, .w = TILE_WIDTH, .h = TILE_HEIGHT };
  SDL_Rect dst = { .x = dx, .y = dy, .w = TILE_WIDTH, .h = TILE_HEIGHT };
  SDL_BlitSurface(tiles_, &src, window_surface_, &dst);
}
