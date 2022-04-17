#pragma once

#include <vector>
#include <memory>

#include "config.h"
#include "renderer.h"
#include "objects/object.h"
#include "objects/player.h"

class Map {
 public:
  Map(Renderer &renderer, int x, int y, int w, int h)
    : renderer_(renderer), x_(x), y_(y), w_(w), h_(h) {}

  Map(Renderer &renderer)
    : Map(renderer, MAP_POS_X, MAP_POS_Y, MAP_WIDTH, MAP_HEIGHT) {}

  int load_map(const char *fname);

  void render();

  void render_tile(int sx, int sy, int dx, int dy) const;
  void render_tile(int sx, int sy, int dx, int dy, double angle) const;

  std::vector<Object *>& get_objects();
  void remove_object(Object *o);

  Player *get_player() const;

  int get_x() const { return x_; }

  int get_y() const { return y_; }

  int get_w() const { return w_; }

  int get_h() const { return h_; }

 private:
 	Renderer renderer_;
  std::vector<Object*> objects_;
  Player *player_;

  const int x_;
  const int y_;
  const int w_;
  const int h_;
};