#include <cstdio>
#include <cstdlib>
#include "map.h"

int Map::load_map(const char *fname) {
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

      int x = MAP_POS_X + w * TILE_WIDTH;
      int y = MAP_POS_Y + h * TILE_HEIGHT;

      char c = map[h * (MAP_TILES_WIDTH + 1) + w];

      switch (c) {
        case 'W': {
          objects_.push_back(new Wall(this, x, y, TILE_WIDTH, TILE_HEIGHT));
          break;
        }
        case 'S': {
          objects_.push_back(new Stone(this, x, y, TILE_WIDTH, TILE_HEIGHT));
          break;
        }
        case ' ': {
          objects_.push_back(new Grass(this, x, y, TILE_WIDTH, TILE_HEIGHT));
          break;
        }
        case 'P': {
          objects_.push_back(new Grass(this, x, y, TILE_WIDTH, TILE_HEIGHT));
          player_ = new Player(this, x, y, TILE_WIDTH, TILE_HEIGHT);
          break;
        }
      }
    }
  }
  
  return 0;
}

std::vector<Object *>& Map::get_objects() {
  return objects_;
}

Player *Map::get_player() const {
  return player_;
}

void Map::render() {
  for (Object *o: objects_) {
    o->render(renderer_);
  }
  player_->render(renderer_);
}

