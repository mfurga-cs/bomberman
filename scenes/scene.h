#pragma once

#include "../renderer.h"
#include "../context.h"

class SceneManager;

class Scene {
 public:
  Scene(SceneManager *manager, Renderer *renderer, Context *context)
    : manager_(manager), renderer_(renderer), context_(context) {}

  virtual ~Scene() {};

  virtual void render() = 0;

 protected:
  SceneManager *manager_;
  Renderer *renderer_;
  Context *context_;
};


