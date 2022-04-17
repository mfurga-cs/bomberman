#include <cstdio>
#include <vector>
#include <SDL2/SDL.h>

#include "config.h"
#include "objects/bomb.h"
#include "renderer.h"
#include "map.h"

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

    if (renderer_.init(window_) != 0) {
      SDL_DestroyWindow(window_);
      SDL_Quit();
      return 3;
    }


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

      renderer_.update();
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

    for (Object *obj: map_->get_objects()) {
      if (obj->get_type() != OBJ_BOMB) {
        continue;
      }
      ((Bomb *)obj)->decrease_explosion_time(diff_);
    }

    if (key_pressed_[SDL_SCANCODE_SPACE]) {
      if (space_wait_ == 0) {
        player->place_bomb();
      }
      space_wait_ = 1;
    } else {
      space_wait_ = 0;
    }
    
    map_->render();
  }

  SDL_Window *window_;
  Renderer renderer_;

  bool key_pressed_[1024] = {false};
  int space_wait_ = 0;

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
