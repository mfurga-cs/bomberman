#pragma once

#include <vector>
#include <memory>

#include "config.h"
#include "renderer.h"
#include "objects/object.h"
#include "objects/static.h"
#include "objects/player.h"
#include "objects/enemy.h"

class Map {
 public:
  Map(Renderer &renderer, int x, int y, int w, int h)
    : renderer_(renderer), x_(x), y_(y), w_(w), h_(h) {}

  Map(Renderer &renderer)
    : Map(renderer, MAP_POS_X, MAP_POS_Y, MAP_WIDTH, MAP_HEIGHT) {}

  ~Map();

  int load_map(const char *fname);

  void render();

  void render_tile(int sx, int sy, int dx, int dy) const;
  void render_tile(int sx, int sy, int dx, int dy, double angle) const;

  std::vector<Object *>& get_objects();
  std::vector<Enemy *>& get_enemies();

  StaticObject *get_static_object(int x, int y);

  void add_object(Object *o);

  void remove_object(Object *o);

  void remove_enemy(Enemy *e);

  Player *get_player() const;

  int get_stones_count() const;

  int get_x() const { return x_; }

  int get_y() const { return y_; }

  int get_w() const { return w_; }

  int get_h() const { return h_; }

 private:
  Renderer renderer_;
  std::vector<Object*> objects_;
  std::vector<Enemy *> enemies_;
  StaticObject *static_objects_[MAP_HEIGHT_IN_TILES][MAP_WIDTH_IN_TILES] = { nullptr };

  Player *player_;
  int stone_count_ = 0;

  const int x_;
  const int y_;
  const int w_;
  const int h_;
};