#pragma once

#include <vector>

#include "renderer.h"
#include "objects/object.h"
#include "objects/wall.h"

#define MAP_WIDTH 1200
#define MAP_HEIGHT 720

#define MAP_POS_X   0
#define MAP_POS_Y   80

#define TILE_WIDTH 48
#define TILE_HEIGHT 48

#define MAP_TILES_WIDTH 25
#define MAP_TILES_HEIGHT 15

class Map {
 public:
  Map(Renderer &renerer, int w, int h, int x, int y)
    : renderer_(renerer), w_(w), h_(h), x_(x), y_(y) {}

  int load_map(const char *fname) {
    char map[(MAP_TILES_WIDTH + 1) * MAP_TILES_HEIGHT];

    FILE *f = fopen(fname, "r");
    if (f == NULL) {
      printf("Failed to open map %s\n", fname);
      return 1;
    }
    fread(map, 1, sizeof(map), f);
    fclose(f);

    for (int h = 0; h < MAP_TILES_HEIGHT; h++) {
      for (int w = 0; w < MAP_TILES_WIDTH; w++) {

        int x = w * TILE_WIDTH;
        int y = h * TILE_HEIGHT;

        char c = map[h * (MAP_TILES_WIDTH + 1) + w];

        switch (c) {
          case 'W': {
            Wall *wall = new Wall(x, y, TILE_WIDTH, TILE_HEIGHT);
            wall->render(renderer_);
            break;
          }
          // case 'S': {
          //   SDL_Rect src = { .x = TILE_WIDTH, .y = 0, .w = TILE_WIDTH, .h = TILE_HEIGHT };
          //   objects_.push_back(new Object(OBJ_STONE, x, y, TILE_WIDTH, TILE_HEIGHT, src));
          //   break;
          // }
          // case ' ': {
          //   SDL_Rect src = { .x = TILE_WIDTH * 2, .y = 0, .w = TILE_WIDTH, .h = TILE_HEIGHT };
          //   objects_.push_back(new Object(OBJ_GRASS, x, y, TILE_WIDTH, TILE_HEIGHT, src));
          //   break;
          // }
          // case 'P': {
          //   SDL_Rect src = { .x = 0, .y = TILE_WIDTH, .w = TILE_WIDTH, .h = TILE_HEIGHT };
          //   objects_.push_back(new Player(x, y, TILE_WIDTH, TILE_HEIGHT, src));
          //   break;
          // }
        }
      }
    }
  }

  int x(int x) const {
    return x_ + x;
  }

  int y(int y) const {
    return y_ + y;
  }

 private:
 	Renderer renderer_;
  std::vector<Object*> objects_;
  int w_;
  int h_;
  int x_;
  int y_;
};