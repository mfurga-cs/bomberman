#include "enemy.h"
#include "../map.h"

#include <cstdlib>

ObjectType Enemy::get_type() const {
  return OBJ_ENEMY;
}

void Enemy::render() {
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

  map_->render_tile(tile_x, tile_y, x_, y_);
}

void Enemy::set_velocity(int velocity) {
  velocity_ = 1000 / velocity;
}

void Enemy::move(int time) {
  move_time_ += time;
  if (move_time_ < velocity_) {
    return;
  }
  move_time_ -= velocity_;

  if (change_direction_ == 0) {
    if (can_change_direction()) {
      set_random_direction();
      change_direction_ = (rand() % 300) + 100;
      // printf("%d\n", change_direction_);
    }
  } else {
    --change_direction_;
  }

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
    if (o->get_type() == OBJ_GRASS || o == this) {
      continue;
    }
    if (o->check_collision(*this)) {
      set_next_direction();
      x_ = px;
      y_ = py;
      break;
    }
  }
  
  if (map_->get_player()->check_collision_margin(*this, MARGIN)) {
    map_->get_player()->set_lose();
  }

  last_animation_++;
  if (last_animation_ == ANIMATION_PER_PIXELS) {
    if (tile_style_ == 5) {
      tile_style_ = 6;
    } else if (tile_style_ == 6) {
      tile_style_ = 5;
    }
    last_animation_ = 0;
  }
}

void Enemy::set_next_direction() {
  switch (direction_) {
    case DIRECTION_UP:    direction_ = DIRECTION_RIGHT; break;
    case DIRECTION_RIGHT: direction_ = DIRECTION_DOWN;  break;
    case DIRECTION_DOWN:  direction_ = DIRECTION_LEFT;  break;
    case DIRECTION_LEFT:  direction_ = DIRECTION_UP;    break;
  }
}

Direction direction_from_int(int direction) {
  switch (direction) {
    case 0: return DIRECTION_LEFT;
    case 1: return DIRECTION_UP;
    case 2: return DIRECTION_RIGHT;
    case 3: return DIRECTION_DOWN;
  }
  return DIRECTION_RIGHT;
}

void Enemy::set_random_direction() {

  if (rand() % 100 <= 30) {
    direction_ = direction_from_int(rand() % 4);
    return;
  }

  Player *player = map_->get_player();

  int px = player->get_x();
  int py = player->get_y();
  int dx = std::abs(x_ - px);
  int dy = std::abs(y_ - py);

  if (dx > dy) {
    if (px >= x_) {
      direction_ = DIRECTION_RIGHT;
    } else {
      direction_ = DIRECTION_LEFT;
    }
  } else {
    if (py >= y_) {
      direction_ = DIRECTION_DOWN;
    } else {
      direction_ = DIRECTION_UP;
    }
  }
}

bool Enemy::can_change_direction() const {
  return x_ % w_ == 0 && y_ % h_ == 0;
}