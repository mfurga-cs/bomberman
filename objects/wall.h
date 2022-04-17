#pragma once

#include "static.h"

class Wall: public StaticObject {
 public:
  Wall(Map *map, int x, int y, int w, int h)
    : StaticObject(map, x, y, w, h) {}

  Wall(Map *map, int x, int y)
    : StaticObject(map, x, y) {}

  ~Wall() {}

  ObjectType get_type() const {
    return OBJ_WALL;
  }

  void render() {
    map_->render_tile(TILE_X, TILE_Y, x_, y_);
  }

 private:
  constexpr static int TILE_X = 0;
  constexpr static int TILE_Y = 0; 
};