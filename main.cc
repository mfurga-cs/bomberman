#include <cstdio>
#include <vector>
#include <string>
#include <SDL2/SDL.h>

#include "config.h"
#include "renderer.h"
#include "context.h"
#include "scenes/scene_manager.h"

class Game {
 public:
  Game() {}

  ~Game() {
    SDL_DestroyWindow(window_);
    SDL_Quit();
  }

  int init() {
    srand(time(0));

    if (TTF_Init() != 0) {
      return 1;
    }

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

    manager_ = new SceneManager(&renderer_, &context_);

    return 0;
  }

  void start() {
    context_.t_now = SDL_GetTicks();
    context_.t_diff = 0;

    SDL_Event event;
    context_.end = false;

    // manager_->set_scene(SCENE_GAME_OVER);
    manager_->set_scene(SCENE_PLAY);

    while (!context_.end) {

      while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
          context_.end = true;
        }

        if (event.type == SDL_KEYDOWN) {
          context_.key_pressed[event.key.keysym.scancode] = true;
        }

        if (event.type == SDL_KEYUP) {
          context_.key_pressed[event.key.keysym.scancode] = false;
        }
      }

      manager_->render();

      int now = SDL_GetTicks();
      context_.t_diff = now - context_.t_now;
      context_.t_now = now;

      renderer_.update();
    }

  }

 private:
  SDL_Window *window_;
  Renderer renderer_;
  Context context_;
  SceneManager *manager_;
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
