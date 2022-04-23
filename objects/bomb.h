#pragma once

#include "static.h"
#include "../renderer.h"

class Bomb: public StaticObject {
 public:
  Bomb(Map *map, int x, int y, int w, int h, int power)
    : StaticObject(map, x, y, w, h),
      power_(power),
      explosion_time_(EXPLOSION_TIME) {}

  Bomb(Map *map, int x, int y, int power)
    : StaticObject(map, x, y), power_(power), explosion_time_(EXPLOSION_TIME) {}

  ~Bomb() {}

  ObjectType get_type() const {
    return OBJ_BOMB;
  }

  void render();

  void set_explosion_time(int time);
  int get_explosion_time() const;
  void decrease_explosion_time(int delta);

 private:

  void remove_objects_(bool remove);

  void remove_enemy_(StaticObject *so);

  int power_;
  int explosion_time_;
  int tile_style_ = 0;
  bool player_killed_ = false;

  constexpr static int EXPLOSION_TIME = 2000;
  constexpr static int ANIMATION_TIME = 700;
  constexpr static int MARGIN = 10;

  constexpr static int TILE_BOMB_X = TILE_WIDTH * 4;
  constexpr static int TILE_BOMB_Y = TILE_HEIGHT;

  constexpr static int TILE_EXPLOSION_CENTER_X = 0;
  constexpr static int TILE_EXPLOSION_CENTER_Y = TILE_HEIGHT * 4;

  constexpr static int TILE_EXPLOSION_MID_X = TILE_WIDTH;
  constexpr static int TILE_EXPLOSION_MID_Y = TILE_HEIGHT * 4;

  constexpr static int TILE_EXPLOSION_END_X = TILE_WIDTH * 2;
  constexpr static int TILE_EXPLOSION_END_Y = TILE_HEIGHT * 4;
};