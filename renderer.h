#pragma once

#include "config.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class Renderer {
 public:
  Renderer() {}

  int init(SDL_Window *window);

  void update() const;

  int load_tiles(const char *fname);

  int load_font(const char *fname);

  void render_tile(int sx, int sy, int dx, int dy) const;

  void render_tile(int sx, int sy, int dx, int dy, double angle) const;

  void render_string(const char *str, int x, int y) const;

  void render_string_right(const char *str, int x, int y) const;

  SDL_Renderer *get_renderer();

 private:
  void render_string_(const char *str, int x, int y, bool right) const;

  // SDL_Surface *tiles_;
  SDL_Surface *window_surface_;

  SDL_Renderer *renderer_;
  SDL_Texture *tiles_;
  TTF_Font *font_;
};
