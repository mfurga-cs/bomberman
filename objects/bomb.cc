#include "../map.h"
#include "bomb.h"

void Bomb::set_explosion_time(int time) {
  explosion_time_ = time;
}

int Bomb::get_explosion_time() const {
  return explosion_time_;
}

void Bomb::render(const Renderer &renderer) {
  if (explosion_time_ > 0) {
    renderer.render_tile(TILE_X, TILE_Y * tile_style_, x_, y_);
  } else {

    renderer.render_tile(TILE_WIDTH * 0, TILE_HEIGHT * 4, x_, y_);

    renderer.render_tile(TILE_WIDTH * 2, TILE_HEIGHT * 4, x_ + w_, y_);
    renderer.render_tile(TILE_WIDTH * 2, TILE_HEIGHT * 4, x_ - w_, y_, 180);
    renderer.render_tile(TILE_WIDTH * 2, TILE_HEIGHT * 4, x_, y_ + h_, 90);
    renderer.render_tile(TILE_WIDTH * 2, TILE_HEIGHT * 4, x_, y_ - h_, -90);

    // renderer.render_tile(TILE_WIDTH * 2, TILE_HEIGHT * 4, x_ + 2 * w_, y_);
    // renderer.render_tile(TILE_WIDTH * 2, TILE_HEIGHT * 4, x_ - 2 * w_, y_, 180);
    // renderer.render_tile(TILE_WIDTH * 2, TILE_HEIGHT * 4, x_, y_ + 2 * h_, 90);
    // renderer.render_tile(TILE_WIDTH * 2, TILE_HEIGHT * 4, x_, y_ - 2 * h_, -90);
  }
}

void Bomb::decrease_explosion_time(int delta) {
  explosion_time_ -= delta;

  if (explosion_time_ > 2 * EXPLOSION_TIME / 3) {
    tile_style_ = 0;
  } else if (explosion_time_ > EXPLOSION_TIME / 3) {
    tile_style_ = 1;
  } else {
    tile_style_ = 2;
  }

  if (-1 * explosion_time_ > ANIMATION_TIME) {
    map_->remove_object(this);
  }
}

