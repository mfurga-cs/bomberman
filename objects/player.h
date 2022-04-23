#pragma once

#include "object.h"

class Player: public Object {
 public:
  Player(Map *map, int x, int y, int w, int h)
    : Object(map, x, y, w, h), direction_(DIRECTION_DOWN), tile_style_(1) {
      set_velocity(150);
      last_animation_ = 0;
    }

  Player(Map *map, int x, int y)
    : Object(map, x, y), direction_(DIRECTION_DOWN), tile_style_(1) {
      set_velocity(150);
      last_animation_ = 0;
    }

  ~Player() {}

  ObjectType get_type() const;

  void render();

  void set_velocity(int velocity);

  void set_direction(Direction direction);

  int get_points() const;
  void add_points(int points);

  void add_bomb();
  int get_bomb_power() const;

  bool get_lose();
  void set_lose();
 
  void move(int time);

  void stop();

  void place_bomb();

 private:
  void move_jump(Object *o);

  Direction direction_;
  int velocity_;
  int move_time_ = 0;
  int points_ = 0;
  int bombs_ = 1;
  bool lose_ = false;

  // TODO: Move to animation
  int tile_style_;
  // In pixels
  int last_animation_;

  constexpr static int JUMP_FROM = 8;
  constexpr static int ANIMATION_PER_PIXELS = 12;
};