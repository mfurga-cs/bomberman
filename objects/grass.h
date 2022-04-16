#pragma once

#include "object.h"
#include "../renderer.h"

class Grass: public Object {
 public:
  Grass(Map *map, int x, int y, int w, int h)
    : Object(map, x, y, w, h) {}
  ~Grass() {}

  ObjectType get_type() const {
    return OBJ_GRASS;
  }

  void render(const Renderer &renderer) {
    renderer.render_tile(TILE_X, TILE_Y, x_, y_);
  }

 private:
  constexpr static int TILE_X = TILE_WIDTH * 2;
  constexpr static int TILE_Y = 0; 
};