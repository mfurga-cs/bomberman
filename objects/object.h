#pragma once

#include "../renderer.h"

enum ObjectType {
  OBJ_WALL = 0,
  OBJ_STONE,
  OBJ_GRASS,
  OBJ_PLAYER
};

class Object {
 public:
  Object(int x, int y, int w, int h)
    : x_(x), y_(y), w_(w), h_(h) {} 

  int get_x() const { return x_; }

  int get_y() const { return y_; }

  virtual ObjectType get_type() const = 0;
  virtual void render(const Renderer &renderer) const = 0;

 protected:
  int x_;
  int y_;
  int w_;
  int h_;
};