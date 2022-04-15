#pragma once

#include "object.h"
#include "../renderer.h"

class Wall: public Object {
 public:
  Wall(int x, int y, int w, int h): Object(x, y, w, h) {}
  ~Wall() {}

  ObjectType get_type() const {
    return OBJ_WALL;
  }

  void render(const Renderer &renderer) const {
    renderer.render_tile(TILE_X, TILE_Y, x_, y_);
  }

 private:
  constexpr static int TILE_X = 0;
  constexpr static int TILE_Y = 0; 
};