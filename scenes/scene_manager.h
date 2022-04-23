#pragma once

#include "scene.h"
#include "play.h"
#include "game_over.h"
#include "../context.h"

enum SceneType {
  SCENE_PLAY = 0,
  SCENE_GAME_OVER,
  SCENE_LENGTH
};

class SceneManager {
 public:
  SceneManager(Renderer *renderer, Context *context) {
    scenes_[SCENE_PLAY] = new PlayScene(this, renderer, context);
    scenes_[SCENE_GAME_OVER] = new GameOverScene(this, renderer, context);
    current_ = SCENE_PLAY;
    scenes_[current_]->init();
  }

  void set_scene(const SceneType scene) {
    scenes_[current_]->end();
    current_ = scene;
    scenes_[current_]->init();
  }

  void render() {
    scenes_[current_]->render();
  }

 private:
  SceneType current_;
  Scene* scenes_[SCENE_LENGTH];
};
