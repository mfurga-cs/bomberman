#include <cstdio>
#include <vector>
#include <SDL2/SDL.h>
#include "object.h"

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800

#define MAP_WIDTH 1200
#define MAP_HEIGHT 720

#define MAP_POS_X   0
#define MAP_POS_Y   80


#define TILE_WIDTH 48
#define TILE_HEIGHT 48

#define MAP_TILES_WIDTH 25
#define MAP_TILES_HEIGHT 15

// void render() {

//   if (key_pressed[SDL_SCANCODE_DOWN]) {

//     if (time_in > 10) {
//       {
//         printf("%d\n", time_in);
//         SDL_Rect src { .x = TILE_WIDTH * 2, .y = 0, .w = TILE_WIDTH, .h = TILE_HEIGHT };
//         SDL_Rect dst { .x = init_pos_x, .y = init_pos_y, .w = 48, .h = 48 };
//         SDL_BlitSurface(map_surface, &src, window_surface, &dst);
//       }

//       SDL_Rect src;

//       if (before == 1) {
//         if (time_animation > 100) {
//           src.x = 0; src.y = 102; src.w = 48; src.h = 48;
//           before = 2;
//           time_animation = 0;
//         } else {
//           src.x = 0; src.y = 51; src.w = 48; src.h = 48;
//         }
//       } else if (before == 2 || before == 0) {
//         if (time_animation > 100) {
//           src.x = 0; src.y = 51; src.w = 48; src.h = 48;
//           before = 1;
//           time_animation = 0;
//         } else {
//           src.x = 0; src.y = 102; src.w = 48; src.h = 48;
//         }
//       }
      
//       SDL_Rect dst { .x = init_pos_x, .y = init_pos_y + 1, .w = 48, .h = 48 };
//       SDL_BlitSurface(character_surface, &src, window_surface, &dst);
//       init_pos_y += 1;
//       time_in = 0;
//     }

//     time_in += time_diff;
//     time_animation += time_diff;
//   } else {
//     SDL_Rect src { .x = 0, .y = 0, .w = TILE_WIDTH, .h = TILE_HEIGHT };
//     SDL_Rect dst { .x = init_pos_x, .y = init_pos_y, .w = 48, .h = 48 };
//     SDL_BlitSurface(character_surface, &src, window_surface, &dst);
//     time_in = 0;
//   }
// }




class Map {
 public:
  Map(SDL_Surface *s, int w, int h, int x, int y)
    : s_(s), w_(w), h_(h), x_(x), y_(y) {}

  int load_tiles(const char *fname) {
    t_ = SDL_LoadBMP(fname);
    if (t_ == NULL) {
      puts("SDL_LoadBMP failed");
      return 1;
    }
    return 0;
  }

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
            SDL_Rect src = { .x = 0, .y = 0, .w = TILE_WIDTH, .h = TILE_HEIGHT };
            objects_.push_back(new Object(OBJ_WALL, x, y, TILE_WIDTH, TILE_HEIGHT, src));
            break;
          }
          case 'S': {
            SDL_Rect src = { .x = TILE_WIDTH, .y = 0, .w = TILE_WIDTH, .h = TILE_HEIGHT };
            objects_.push_back(new Object(OBJ_STONE, x, y, TILE_WIDTH, TILE_HEIGHT, src));
            break;
          }
          case ' ': {
            SDL_Rect src = { .x = TILE_WIDTH * 2, .y = 0, .w = TILE_WIDTH, .h = TILE_HEIGHT };
            objects_.push_back(new Object(OBJ_GRASS, x, y, TILE_WIDTH, TILE_HEIGHT, src));
            break;
          }
          case 'P': {
            SDL_Rect src = { .x = 0, .y = TILE_WIDTH, .w = TILE_WIDTH, .h = TILE_HEIGHT };
            objects_.push_back(new Player(x, y, TILE_WIDTH, TILE_HEIGHT, src));
            break;
          }
        }
      }
    }
  }

  void render() {
    for (Object *o : objects_) {
      o->render(s_, t_);
    }
  }

  int x(int x) const {
    return x_ + x;
  }

  int y(int y) const {
    return y_ + y;
  }

 private:
  SDL_Surface *s_;
  SDL_Surface *t_;
  std::vector<Object*> objects_;
  int w_;
  int h_;
  int x_;
  int y_;
};


class Game {
 public:
  Game() {}

  ~Game() {

    if (map_ != nullptr) {
      delete map_;
    }

    SDL_DestroyWindow(window_);
    SDL_Quit();
  }

  int init() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_EVENTS) != 0) {
      return 1;
    }

    window_ = SDL_CreateWindow(
      "Bomberman",
      SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED,
      WINDOW_WIDTH,
      WINDOW_HEIGHT,
      SDL_WINDOW_OPENGL
    );

    if (window_ == NULL) {
      return 2;
    }

    window_surface_ = SDL_GetWindowSurface(window_);
    if (window_surface_ == NULL) {
      SDL_DestroyWindow(window_);
      SDL_Quit();
      return 3;
    }

    return 0;
  }

  void start() {

    map_ = new Map(window_surface_, MAP_WIDTH, MAP_HEIGHT, MAP_POS_X, MAP_POS_Y);
    map_->load_tiles("assets/tiles.bmp");
    map_->load_map("assets/map1");
    map_->render();

    // Init timers.
    time_ = SDL_GetTicks();
    diff_ = 0;

    SDL_Event event;
    bool end = false;

    while (!end) {

      while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
          end = true;
        }

        if (event.type == SDL_KEYDOWN) {
          key_pressed_[event.key.keysym.scancode] = true;
        }

        if (event.type == SDL_KEYUP) {
          key_pressed_[event.key.keysym.scancode] = false;
        }
      }

      render_frame();

      int now = SDL_GetTicks();
      diff_ = now - time_;
      time_ = now;

      SDL_UpdateWindowSurface(window_);
    }

  }

 private:

  void render_frame() {

  }

  SDL_Window *window_;
  SDL_Surface *window_surface_;

  bool key_pressed_[1024];

  int time_;
  int diff_;

  Map *map_ = nullptr;
};


int main(void)
{
  Game game;
  if (game.init() != 0) {
    puts("Game initialization failed.");
    return 1;
  }

  game.start();

  return 0;
}
