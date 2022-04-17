#pragma once

class StaticObject {
 public:
  virtual int get_static_x() const = 0;
  virtual int get_static_y() const = 0;

 private:
  int static_x;
  int static_y;
};

