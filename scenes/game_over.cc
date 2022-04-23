#include "game_over.h"
#include "scene_manager.h"

GameOverScene::GameOverScene(SceneManager *manager, Renderer *renderer, Context *context)
  : Scene(manager, renderer, context), state_(GAME_OVER_PLAY_AGAIN) {}

void GameOverScene::render() {

  // SDL_SetRenderDrawColor(renderer_->get_renderer(), 0x9e, 0x9e, 0x9e, 255);
  SDL_RenderClear(renderer_->get_renderer());

  if (context_->key_pressed[SDL_SCANCODE_DOWN] || context_->key_pressed[SDL_SCANCODE_UP]) {

    if (!arrow_wait_) {
      if (state_ == GAME_OVER_PLAY_AGAIN) {
        state_ = GAME_OVER_EXIT;
      } else {
        state_ = GAME_OVER_PLAY_AGAIN;
      }  
    }

    arrow_wait_ = true;
  } else if (context_->key_pressed[SDL_SCANCODE_RETURN]) {
    if (state_ == GAME_OVER_PLAY_AGAIN) {
      manager_->set_scene(SCENE_PLAY);
    } else {
      context_->end = true;
    }
  } else {
    arrow_wait_ = false;
  }

  // 38952b

  SDL_Color color = { .r = 0x2e, .g = 0x2e, .b = 0x2e, .a = 255 };
  SDL_Color active = { .r = 0x38, .g = 0x95, .b = 0x52, .a = 255 };

  renderer_->render_string(context_->message, 80, color, 380, 270);
  std::string score = "YOUR SCORE: ";
  score += std::to_string(context_->points);

  renderer_->render_string(score.c_str(), 30, color, 380, 350);

  switch (state_) {
    case GAME_OVER_PLAY_AGAIN:
      renderer_->render_string("PLAY AGAIN", 40, active, 380, 400);
      renderer_->render_string("EXIT", 40, color, 380, 450);
    break;

    case GAME_OVER_EXIT:
      renderer_->render_string("PLAY AGAIN", 40, color, 380, 400);
      renderer_->render_string("EXIT", 40, active, 380, 450);
    break;
  }
}

