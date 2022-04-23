#pragma once

#include "../config.h"
#include <algorithm>
#include <cstdio>

class Map;

enum Direction {
  DIRECTION_UP = 0,
  DIRECTION_RIGHT,
  DIRECTION_DOWN,
  DIRECTION_LEFT
};

enum ObjectType {
  OBJ_WALL = 0,
  OBJ_STONE,
  OBJ_GRASS,
  OBJ_BOMB,
  OBJ_PLAYER,
  OBJ_ENEMY
};

class Object {
 public:
  Object(Map *map, int x, int y, int w, int h)
    : map_(map), x_(x), y_(y), w_(w), h_(h) {}

  Object(Map *map, int x, int y)
    : Object(map, x, y, TILE_WIDTH, TILE_HEIGHT) {}

  virtual ~Object() {};

  int get_x() const { return x_; }

  int get_y() const { return y_; }

  int get_w() const { return w_; }

  int get_h() const { return h_; }

  Map *get_map() { return map_; }


  bool check_collision(const Object& o) const {
    return x_ < o.x_ + o.w_ && x_ + w_ > o.x_ &&
           y_ < o.y_ + o.h_ && y_ + h_ > o.y_;
  }

  bool check_collision_margin(const Object& o, unsigned margin) {
    if (!check_collision(o)) {
      return false;
    }
    unsigned x1 = std::max(x_, o.get_x());
    unsigned x2 = std::min(x_ + w_, o.get_x() + o.get_w());
    unsigned y1 = std::max(y_, o.get_y());
    unsigned y2 = std::min(y_ + h_, o.get_y() + o.get_h());
    return x2 - x1 > margin && y2 - y1 > margin;
  }

  // A   ---
  // B  ---
  
  // a_x = 2, a_w = 3
  // b_x = 1, b_w = 3

  // x1 = 2, x2 = 4
  // 3 - 1 = 2

  virtual bool is_static() const {
    return false;
  }

  virtual ObjectType get_type() const = 0;
  virtual void render() = 0;

 protected:
  Map *map_ = nullptr;
  int x_;
  int y_;
  int w_;
  int h_;
};