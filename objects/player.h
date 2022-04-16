#pragma once

#include "object.h"
#include "../renderer.h"

enum Direction {
  DIRECTION_UP = 0,
  DIRECTION_RIGHT,
  DIRECTION_DOWN,
  DIRECTION_LEFT
};

class Player: public Object {
 public:
  Player(Map *map, int x, int y, int w, int h)
    : Object(map, x, y, w, h), direction_(DIRECTION_DOWN), tile_style_(1) {
      set_velocity(200);
    }
  ~Player() {}

  ObjectType get_type() const;

  void render(const Renderer &renderer);

  void set_velocity(int velocity);

  void set_direction(Direction direction);

  void move(int time);

  void stop();

 private:
  Direction direction_;
  int velocity_;
  int move_time_ = 0;

  // TODO: Move to animation
  int tile_style_;
};