#pragma once

#include "../config.h"

class Map;

enum ObjectType {
  OBJ_WALL = 0,
  OBJ_STONE,
  OBJ_GRASS,
  OBJ_BOMB,
  OBJ_PLAYER
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

  virtual ObjectType get_type() const = 0;
  virtual void render() = 0;

 protected:
  Map *map_ = nullptr;
  int x_;
  int y_;
  int w_;
  int h_;
};