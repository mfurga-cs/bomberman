#include "player.h"
#include "../map.h"

ObjectType Player::get_type() const {
  return OBJ_PLAYER;
}

void Player::render(const Renderer &renderer) {
  int tile_x = 0;
  int tile_y = 0;

  switch (direction_) {
    case DIRECTION_UP:
      tile_x = TILE_WIDTH * 2;
      tile_y = TILE_HEIGHT * tile_style_;
    break;
    case DIRECTION_RIGHT:
      tile_x = TILE_WIDTH * 1;
      tile_y = TILE_HEIGHT * tile_style_;
    break;
    case DIRECTION_DOWN:
      tile_x = 0;
      tile_y = TILE_HEIGHT * tile_style_;
    break;
    case DIRECTION_LEFT:
      tile_x = TILE_WIDTH * 3;
      tile_y = TILE_HEIGHT * tile_style_;
    break;
  }
 
  renderer.render_tile(tile_x, tile_y, x_, y_);
}

void Player::set_velocity(int velocity) {
  velocity_ = 1000 / velocity;
}

void Player::set_direction(Direction direction) {
  direction_ = direction;
}

void Player::move(int time) {
  move_time_ += time;
  if (move_time_ < velocity_) {
    return;
  }
  move_time_ -= velocity_;

  int px = x_;
  int py = y_;

  switch (direction_) {
    case DIRECTION_UP:
      y_ -= 1;
    break;
    case DIRECTION_RIGHT:
      x_ += 1;
    break;
    case DIRECTION_DOWN:
      y_ += 1;
    break;
    case DIRECTION_LEFT:
      x_ -= 1;
    break;
  }

  for (Object *o: map_->get_objects()) {
    if (o->get_type() == OBJ_GRASS) {
      continue;
    }

    if (o->check_collision(*this)) {
      x_ = px;
      y_ = py;
      break;
    }
  }

  if (tile_style_ == 1) {
    tile_style_ = 2;
  } else if (tile_style_ == 2) {
    tile_style_ = 3;
  } else if (tile_style_ == 3) {
    tile_style_ = 2;
  }
}

void Player::stop() {
  // TODO: Move to animation.
  tile_style_ = 1;
}
