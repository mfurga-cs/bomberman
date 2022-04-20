#include "play.h"
#include "../objects/bomb.h"

#include <SDL2/SDL.h>

PlayScene::PlayScene(SceneManager *manager, Renderer *renderer, Context *context)
  : Scene(manager, renderer, context) {

  map_ = new Map(*renderer);
  if (map_->load_map("assets/map1") != 0) {
    puts("Failed to load map.");
    return;
  }
}

void PlayScene::render() {
  Player *player = map_->get_player();

  bool move = false;

  if (context_->key_pressed[SDL_SCANCODE_UP]) {
    player->set_direction(DIRECTION_UP);
    move = true;
  } else if (context_->key_pressed[SDL_SCANCODE_RIGHT]) {
    player->set_direction(DIRECTION_RIGHT);
    move = true;
  } else if (context_->key_pressed[SDL_SCANCODE_DOWN]) {
    player->set_direction(DIRECTION_DOWN);
    move = true;
  } else if (context_->key_pressed[SDL_SCANCODE_LEFT]) {
    player->set_direction(DIRECTION_LEFT);
    move = true;
  }

  if (move) {
    player->move(context_->t_diff);
  } else {
    player->stop();
  }

  for (Object *obj: map_->get_objects()) {
    if (obj->get_type() != OBJ_BOMB) {
      continue;
    }
    ((Bomb *)obj)->decrease_explosion_time(context_->t_diff);
  }

  if (context_->key_pressed[SDL_SCANCODE_SPACE]) {
    if (space_wait_ == 0) {
      player->place_bomb();
    }
    space_wait_ = 1;
  } else {
    space_wait_ = 0;
  }

  SDL_RenderClear(renderer_->get_renderer());

  map_->render();
  // Render panel.

  std::string points = std::to_string(map_->get_player()->get_points());
  renderer_->render_string_right(points.c_str(), 20, 0);

  std::string power = "POWER ";
  power += std::to_string(map_->get_player()->get_bomb_power());
  renderer_->render_string(power.c_str(), 20, 0);
}

