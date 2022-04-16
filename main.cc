#include <cstdio>
#include <vector>
#include <SDL2/SDL.h>

#include "map.h"
#include "renderer.h"

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800

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

    SDL_Surface *window_surface = SDL_GetWindowSurface(window_);
    if (window_surface == NULL) {
      SDL_DestroyWindow(window_);
      SDL_Quit();
      return 3;
    }

    renderer_.set_window_surface(window_surface);
    if (renderer_.load_tiles("assets/tiles.bmp") != 0) {
      return 4;
    }

    map_ = new Map(renderer_);
    if (map_->load_map("assets/map1") != 0) {
      return 5;
    }

    return 0;
  }

  void start() {
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
    Player *player = map_->get_player();

    bool move = false;

    if (key_pressed_[SDL_SCANCODE_UP]) {
      player->set_direction(DIRECTION_UP);
      move = true;
    } else if (key_pressed_[SDL_SCANCODE_RIGHT]) {
      player->set_direction(DIRECTION_RIGHT);
      move = true;
    } else if (key_pressed_[SDL_SCANCODE_DOWN]) {
      player->set_direction(DIRECTION_DOWN);
      move = true;
    } else if (key_pressed_[SDL_SCANCODE_LEFT]) {
      player->set_direction(DIRECTION_LEFT);
      move = true;
    }

    if (move) {
      player->move(diff_);
    } else {
      player->stop();
    }
    
    map_->render();
  }

  SDL_Window *window_;
  Renderer renderer_;

  bool key_pressed_[1024] = {false};

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
