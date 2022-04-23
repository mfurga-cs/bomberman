#pragma once

#include "object.h"

class Enemy: public Object {
 public:
  Enemy(Map *map, int x, int y, int w, int h)
    : Object(map, x, y, w, h), direction_(DIRECTION_DOWN),
      tile_style_(5), last_animation_(0) {
      set_velocity(150);
    }

  Enemy(Map *map, int x, int y)
    : Object(map, x, y), direction_(DIRECTION_DOWN),
      tile_style_(5), last_animation_(0) {
      set_velocity(150);
    }

  ~Enemy() {}

  ObjectType get_type() const;

  void render();

  void set_velocity(int velocity);

  void move(int time);

 private:
  void set_next_direction();
  void set_random_direction();

  bool can_change_direction() const;

  Direction direction_;
  int velocity_;
  int move_time_ = 0;

  // TODO: Move to animation
  int tile_style_;
  // In pixels
  int last_animation_;
  int change_direction_ = 0;

  constexpr static int JUMP_FROM = 8;
  constexpr static int ANIMATION_PER_PIXELS = 12;
  constexpr static int MARGIN = 6;
};