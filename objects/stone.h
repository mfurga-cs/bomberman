#pragma once

#include "static.h"

class Stone: public StaticObject {
 public:
  Stone(Map *map, int x, int y, int w, int h)
    : StaticObject(map, x, y, w, h) {}

  Stone(Map *map, int x, int y)
    : StaticObject(map, x, y) {}

  ~Stone() {}

  ObjectType get_type() const {
    return OBJ_STONE;
  }

  void render() {
    map_->render_tile(TILE_X, TILE_Y, x_, y_);
  }

 private:
  constexpr static int TILE_X = TILE_WIDTH;
  constexpr static int TILE_Y = 0; 
};