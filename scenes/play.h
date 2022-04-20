#pragma once

#include "scene.h"
#include "../map.h"

class SceneManager;

class PlayScene: public Scene {
 public:
  PlayScene(SceneManager *manager, Renderer *renderer, Context *context);
  
  void render();

 private:
  Map *map_;
  int space_wait_ = 0;
};
