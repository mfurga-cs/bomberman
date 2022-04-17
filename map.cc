#include "map.h"
#include "objects/wall.h"
#include "objects/stone.h"
#include "objects/grass.h"

#include <cstdio>
#include <cstdlib>
#include <algorithm>

int Map::load_map(const char *fname) {
  char map[(MAP_WIDTH_IN_TILES + 1) * MAP_HEIGHT_IN_TILES];

  FILE *f = fopen(fname, "r");
  if (f == NULL) {
    printf("Failed to open map %s\n", fname);
    return 1;
  }
  fread(map, 1, sizeof(map), f);
  fclose(f);

  for (int h = 0; h < MAP_HEIGHT_IN_TILES; h++) {
    for (int w = 0; w < MAP_WIDTH_IN_TILES; w++) {

      int x = w * TILE_WIDTH;
      int y = h * TILE_HEIGHT;

      char c = map[h * (MAP_WIDTH_IN_TILES + 1) + w];

      switch (c) {
        case 'W': {
          objects_.push_back(new Wall(this, x, y));
          break;
        }
        case 'S': {
          objects_.push_back(new Stone(this, x, y));
          break;
        }
        case ' ': {
          objects_.push_back(new Grass(this, x, y));
          break;
        }
        case 'P': {
          objects_.push_back(new Grass(this, x, y));
          player_ = new Player(this, x, y);
          break;
        }
      }
    }
  }
  
  return 0;
}

void Map::render_tile(int sx, int sy, int dx, int dy) const {
  render_tile(sx, sy, dx, dy, 0);
}

void Map::render_tile(int sx, int sy, int dx, int dy, double angle) const {
  renderer_.render_tile(sx, sy, x_ + dx, y_ + dy, angle);
}

std::vector<Object *>& Map::get_objects() {
  return objects_;
}

void Map::remove_object(Object *o) {
  std::vector<Object *>::iterator pos = std::find(objects_.begin(), objects_.end(), o);
  if (pos != objects_.end()) {
    objects_.erase(pos);
  }
  delete o;
}

Player *Map::get_player() const {
  return player_;
}

void Map::render() {
  for (Object *o: objects_) {
    o->render();
  }
  player_->render();
}

