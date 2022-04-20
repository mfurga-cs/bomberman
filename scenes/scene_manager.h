#pragma once

#include "scene.h"
#include "play.h"
#include "../context.h"

enum SceneType {
  SCENE_PLAY,
  SCENE_LENGTH
};

class SceneManager {
 public:
  SceneManager(Renderer *renderer, Context *context) {
    scenes_[SCENE_PLAY] = new PlayScene(this, renderer, context);
  }

  void set_scene(const SceneType scene) {
    current_ = scene;
  }

  void render() {
    scenes_[current_]->render();
  }

 private:
  SceneType current_;
  Scene* scenes_[SCENE_LENGTH];
};
