#pragma once

#include "object.h"

class StaticObject: public Object {
 public:
  StaticObject(Map *map, int x, int y, int w, int h)
    : Object(map, x, y, w, h) {}

  StaticObject(Map *map, int x, int y)
    : Object(map, x, y) {}

  bool is_static() const {
    return true;
  }

  virtual int get_static_x() const {
    return x_ / TILE_WIDTH;
  }

  virtual int get_static_y() const {
    return y_ / TILE_HEIGHT;
  }
};

