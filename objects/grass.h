#pragma once

#include "static.h"

class Grass: public StaticObject {
 public:
  Grass(Map *map, int x, int y, int w, int h)
    : StaticObject(map, x, y, w, h) {}

  Grass(Map *map, int x, int y)
    : StaticObject(map, x, y) {}

  ~Grass() {}

  ObjectType get_type() const {
    return OBJ_GRASS;
  }

  void render() {
    map_->render_tile(TILE_X, TILE_Y, x_, y_);
  }

 private:
  constexpr static int TILE_X = TILE_WIDTH * 2;
  constexpr static int TILE_Y = 0; 
};