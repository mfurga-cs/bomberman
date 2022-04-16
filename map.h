#pragma once

#include <vector>

#include "renderer.h"
#include "objects/object.h"
#include "objects/wall.h"
#include "objects/stone.h"
#include "objects/grass.h"
#include "objects/player.h"

#define MAP_POS_X   0
#define MAP_POS_Y   80

#define MAP_TILES_WIDTH 25
#define MAP_TILES_HEIGHT 15

class Map {
 public:
  Map(Renderer &renerer): renderer_(renerer) {}

  int load_map(const char *fname);

  void render();

  std::vector<Object *>& get_objects();
  Player *get_player() const;

 private:
 	Renderer renderer_;
  std::vector<Object*> objects_;
  Player *player_;
};