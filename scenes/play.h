#pragma once

#include "scene.h"
#include "../map.h"

class SceneManager;

class PlayScene: public Scene {
 public:
  PlayScene(SceneManager *manager, Renderer *renderer, Context *context);
  
  void init();

  void render();

  void end();

 private:
  Map *map_;
  int space_wait_ = 0;
};
