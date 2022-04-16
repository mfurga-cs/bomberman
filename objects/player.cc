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

  for (Object *o: map_->get_objects()) {
    if (o->get_type() != OBJ_GRASS) {
      continue;
    }
    move_jump(o);
  }

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

void Player::move_jump(Object *o) {
  int x1, x2;
  int y1, y2;

  switch (direction_) {
    case DIRECTION_UP:
    case DIRECTION_DOWN:

      if ((o->get_y() + o->get_h() != y_) && (o->get_y() != y_ + h_)) {
        return;
      }

      x1 = std::max(x_, o->get_x());
      x2 = std::min(x_ + w_, o->get_x() + o->get_w());

      if (x2 - x1 >= o->get_w() - JUMP_FROM) {
        x_ = o->get_x();
      }
    break;
    case DIRECTION_LEFT:
    case DIRECTION_RIGHT:

      if ((o->get_x() + o->get_w() != x_) && (o->get_x() != x_ + w_)) {
        return;
      }

      y1 = std::max(y_, o->get_y());
      y2 = std::min(y_ + h_, o->get_y() + o->get_h());

      if (y2 - y1 >= o->get_h() - JUMP_FROM) {
        y_ = o->get_y();
      }
    break;
  }
}

void Player::stop() {
  // TODO: Move to animation.
  tile_style_ = 1;
}
