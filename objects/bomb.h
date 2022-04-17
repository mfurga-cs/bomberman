#pragma once

#include "object.h"
#include "../renderer.h"

class Bomb: public Object {
 public:
  Bomb(Map *map, int x, int y, int w, int h)
    : Object(map, x, y, w, h), explosion_time_(EXPLOSION_TIME) {}

  Bomb(Map *map, int x, int y)
    : Object(map, x, y), explosion_time_(EXPLOSION_TIME) {}

  ~Bomb() {}

  ObjectType get_type() const {
    return OBJ_BOMB;
  }

  void render();

  void set_explosion_time(int time);
  int get_explosion_time() const;
  void decrease_explosion_time(int delta);

 private:
  int explosion_time_;
  int tile_style_ = 0;

  constexpr static int EXPLOSION_TIME = 4000;
  constexpr static int ANIMATION_TIME = 4000;

  constexpr static int TILE_X = TILE_WIDTH * 4;
  constexpr static int TILE_Y = TILE_HEIGHT; 
};