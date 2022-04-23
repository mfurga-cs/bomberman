#include "map.h"
#include "objects/wall.h"
#include "objects/stone.h"
#include "objects/grass.h"
#include "objects/enemy.h"

#include <cstdio>
#include <cstdlib>
#include <algorithm>

Map::~Map() {
  for (Object *o: objects_) {
    delete o;
  }
}

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
          Wall *wall = new Wall(this, x, y);
          objects_.push_back(wall);
          static_objects_[wall->get_static_y()][wall->get_static_x()] = wall;
          break;
        }
        case 'S': {
          Stone *stone = new Stone(this, x, y);
          objects_.push_back(stone);
          static_objects_[stone->get_static_y()][stone->get_static_x()] = stone;
          break;
        }
        case ' ': {
          Grass *grass = new Grass(this, x, y);
          objects_.push_back(grass);
          static_objects_[grass->get_static_y()][grass->get_static_x()] = grass;
          break;
        }
        case 'P': {
          Grass *grass = new Grass(this, x, y);
          objects_.push_back(grass);
          static_objects_[grass->get_static_y()][grass->get_static_x()] = grass;

          player_ = new Player(this, x, y);
          break;
        }
        case 'E': {
          Grass *grass = new Grass(this, x, y);
          objects_.push_back(grass);
          static_objects_[grass->get_static_y()][grass->get_static_x()] = grass;

          Enemy *enemy = new Enemy(this, x, y);
          enemies_.push_back(enemy);
          break;
        }
      }
    }
  }


  // for (int h = 0; h < MAP_HEIGHT_IN_TILES; h++) {
  //   for (int w = 0; w < MAP_WIDTH_IN_TILES; w++) {

  //     if (static_objects_[h][w] == nullptr) {
  //       printf("N");
  //       continue;
  //     }

  //     switch (static_objects_[h][w]->get_type()) {
  //       case OBJ_STONE:
  //       printf("S");
  //       break;
  //       case OBJ_GRASS:
  //       printf("G");
  //       break;
  //       case OBJ_WALL:
  //       printf("W");
  //       break;
  //     }
  //   }
  //   printf("\n");
  // }

  // printf("\n\n");
  
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

std::vector<Enemy *>& Map::get_enemies() {
  return enemies_;
}

void Map::add_object(Object *o) {
  objects_.push_back(o);
  if (o->is_static() && o->get_type() != OBJ_BOMB) {
    StaticObject *so = (StaticObject *)o;
    static_objects_[so->get_static_y()][so->get_static_x()] = so;
  }
}

void Map::remove_object(Object *o) {
  std::vector<Object *>::iterator pos = std::find(objects_.begin(), objects_.end(), o);
  if (pos != objects_.end()) {
    objects_.erase(pos);
  }

  if (o->is_static() && o->get_type() != OBJ_BOMB) {
    StaticObject *so = (StaticObject *)o;
    static_objects_[so->get_static_y()][so->get_static_x()] = nullptr;
  }

  delete o;
}

void Map::remove_enemy(Enemy *e) {
  std::vector<Enemy *>::iterator pos = std::find(enemies_.begin(), enemies_.end(), e);
  if (pos != enemies_.end()) {
    enemies_.erase(pos);
  }
  delete e;
}

StaticObject *Map::get_static_object(int x, int y) {
  if (x < 0 || y < 0 || x >= MAP_WIDTH_IN_TILES || y >= MAP_HEIGHT_IN_TILES) {
    return nullptr;
  }
  return static_objects_[y][x];
}

Player *Map::get_player() const {
  return player_;
}

void Map::render() {
  std::vector<Enemy *> enemies;

  for (Object *o: objects_) {
    o->render();
  }

  for (Enemy *e: enemies_) {
    e->render();
  }

  player_->render();
}

