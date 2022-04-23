#include "renderer.h"

int Renderer::init(SDL_Window *window) {
  renderer_ = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
  if (renderer_ == NULL) {
    return 1;
  }

  SDL_SetRenderDrawColor(renderer_, 0x9e, 0x9e, 0x9e, 255);
  SDL_RenderClear(renderer_);

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

void Renderer::render_string(const char *str, int size, SDL_Color& color, int x, int y) const {
  render_string_(str, size, color, x, y, false);
}

void Renderer::render_string_right(const char *str, int size, SDL_Color& color, int x, int y) const {
  render_string_(str, size, color, x, y, true);
}

void Renderer::render_string_(const char *str, int size, SDL_Color& color, int x, int y, bool right) const {
  TTF_Font *font = TTF_OpenFont(FONT_LOCATION, size);
  if (font == NULL) {
    printf("TTF_OpenFont: %s\n", TTF_GetError());
    return;
  }

  SDL_Surface *text_surf = TTF_RenderText_Solid(font, str, color);
  if (text_surf == NULL) {
    puts("TTF_RenderText_Solid failed");
    TTF_CloseFont(font);
    return;
  }

  SDL_Texture *text = SDL_CreateTextureFromSurface(renderer_, text_surf);
  if (text == NULL) {
    puts("SDL_CreateTextureFromSurface failed");
    TTF_CloseFont(font);
    return;
  }

  SDL_Rect dst;

  if (right) {
    dst.x = WINDOW_WIDTH - x - text_surf->w; dst.y = y; dst.w = text_surf->w; dst.h = text_surf->h;
  } else {
    dst.x = x; dst.y = y; dst.w = text_surf->w; dst.h = text_surf->h;
  }

  SDL_RenderCopy(renderer_, text, NULL, &dst);

  SDL_DestroyTexture(text);
  SDL_FreeSurface(text_surf);
  TTF_CloseFont(font);
}

SDL_Renderer *Renderer::get_renderer() {
  return renderer_;
}