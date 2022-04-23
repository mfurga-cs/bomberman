#pragma once

#include "scene.h"

enum GameOverState {
  GAME_OVER_PLAY_AGAIN = 0,
  GAME_OVER_EXIT
};

class GameOverScene: public Scene {
 public:
  GameOverScene(SceneManager *manager, Renderer *renderer, Context *context);
  
  void init() {}

  void render();

  void end() {}

 private:
  GameOverState state_;
  bool arrow_wait_ = false;
};

