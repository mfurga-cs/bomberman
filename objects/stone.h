#pragma once

#include "object.h"
#include "../renderer.h"

class Stone: public Object {
 public:
  Stone(Map *map, int x, int y, int w, int h)
    : Object(map, x, y, w, h) {}
  ~Stone() {}

  ObjectType get_type() const {
    return OBJ_STONE;
  }

  void render(const Renderer &renderer) {
    renderer.render_tile(TILE_X, TILE_Y, x_, y_);
  }

 private:
  constexpr static int TILE_X = TILE_WIDTH;
  constexpr static int TILE_Y = 0; 
};