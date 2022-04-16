#include "renderer.h"

int Renderer::init(SDL_Window *window) {
  renderer_ = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
  if (renderer_ == NULL) {
    return 1;
  }
  return 0;
}

void Renderer::update() const {
  SDL_RenderPresent(renderer_);
}

int Renderer::load_tiles(const char *fname) {
  SDL_Surface *surface = SDL_LoadBMP(fname);
  if (surface == NULL) {
    puts("SDL_LoadBMP failed");
    return 1;
  }

  tiles_ = SDL_CreateTextureFromSurface(renderer_, surface);
  if (tiles_ == NULL) {
    SDL_FreeSurface(surface);
    return 2;
  }

  SDL_FreeSurface(surface);
  return 0;
}

void Renderer::render_tile(int sx, int sy, int dx, int dy, double angle) const {
  SDL_Rect src = { .x = sx, .y = sy, .w = TILE_WIDTH, .h = TILE_HEIGHT };
  SDL_Rect dst = { .x = dx, .y = dy, .w = TILE_WIDTH, .h = TILE_HEIGHT };

  SDL_RendererFlip flip = SDL_FLIP_NONE;
  SDL_RenderCopyEx(renderer_, tiles_, &src, &dst, angle, NULL, flip);
}

void Renderer::render_tile(int sx, int sy, int dx, int dy) const {
  render_tile(sx, sy, dx, dy, 0);
}
