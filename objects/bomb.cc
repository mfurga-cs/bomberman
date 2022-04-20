#include "../map.h"
#include "bomb.h"
#include "grass.h"

void Bomb::set_explosion_time(int time) {
  explosion_time_ = time;
}

int Bomb::get_explosion_time() const {
  return explosion_time_;
}

void Bomb::render() {
  if (explosion_time_ > 0) {
    map_->render_tile(TILE_BOMB_X, TILE_BOMB_Y * tile_style_, x_, y_);
  } else {
    int sx = this->get_static_x();
    int sy = this->get_static_y();

    map_->render_tile(TILE_EXPLOSION_CENTER_X, TILE_EXPLOSION_CENTER_Y, x_, y_);

    // RIGHT
    for (int i = 1; i <= power_; i++) {
      StaticObject *so = map_->get_static_object(sx + i, sy);
      if (so == nullptr || so->get_type() == OBJ_WALL) {
        break;
      }

      if (i == power_) {
        map_->render_tile(TILE_EXPLOSION_END_X, TILE_EXPLOSION_END_Y, so->get_x(), so->get_y());
      } else {
        map_->render_tile(TILE_EXPLOSION_MID_X, TILE_EXPLOSION_MID_Y, so->get_x(), so->get_y());
      }

      if (so->get_type() == OBJ_STONE) {
        break;
      }
    }

    // LEFT
    for (int i = 1; i <= power_; i++) {
      StaticObject *so = map_->get_static_object(sx - i, sy);
      if (so == nullptr || so->get_type() == OBJ_WALL) {
        break;
      }

      if (i == power_) {
        map_->render_tile(TILE_EXPLOSION_END_X, TILE_EXPLOSION_END_Y, so->get_x(), so->get_y(), 180);
      } else {
        map_->render_tile(TILE_EXPLOSION_MID_X, TILE_EXPLOSION_MID_Y, so->get_x(), so->get_y(), 180);
      }

      if (so->get_type() == OBJ_STONE) {
        break;
      }
    }

    // UP
    for (int i = 1; i <= power_; i++) {
      StaticObject *so = map_->get_static_object(sx, sy - i);
      if (so == nullptr || so->get_type() == OBJ_WALL) {
        break;
      }

      if (i == power_) {
        map_->render_tile(TILE_EXPLOSION_END_X, TILE_EXPLOSION_END_Y, so->get_x(), so->get_y(), -90);
      } else {
        map_->render_tile(TILE_EXPLOSION_MID_X, TILE_EXPLOSION_MID_Y, so->get_x(), so->get_y(), -90);
      }

      if (so->get_type() == OBJ_STONE) {
        break;
      }
    }

    // DOWN
    for (int i = 1; i <= power_; i++) {
      StaticObject *so = map_->get_static_object(sx, sy + i);
      if (so == nullptr || so->get_type() == OBJ_WALL) {
        break;
      }

      if (i == power_) {
        map_->render_tile(TILE_EXPLOSION_END_X, TILE_EXPLOSION_END_Y, so->get_x(), so->get_y(), 90);
      } else {
        map_->render_tile(TILE_EXPLOSION_MID_X, TILE_EXPLOSION_MID_Y, so->get_x(), so->get_y(), 90);
      }

      if (so->get_type() == OBJ_STONE) {
        break;
      }
    }
  }
}

void Bomb::remove_objects_() {
  int sx = this->get_static_x();
  int sy = this->get_static_y();
  Player *player = map_->get_player();
  StaticObject *so = map_->get_static_object(sx, sy);

  if (player->check_collision_margin(*so, MARGIN)) {
    map_->remove_object(player);
  }

  // RIGHT
  for (int i = 1; i <= power_; i++) {
    so = map_->get_static_object(sx + i, sy);
    if (so == nullptr || so->get_type() == OBJ_WALL) {
      break;
    }

    if (so->get_type() == OBJ_STONE) {
      map_->remove_object(so);
      map_->add_object(new Grass(map_, so->get_x(), so->get_y()));
      map_->get_player()->add_points(POINTS_FOR_STONE);
      break;
    }

    if (player->check_collision_margin(*so, MARGIN)) {
      map_->remove_object(player);
    }
  }

  // LEFT
  for (int i = 1; i <= power_; i++) {
   so = map_->get_static_object(sx - i, sy);
    if (so == nullptr || so->get_type() == OBJ_WALL) {
      break;
    }

    if (so->get_type() == OBJ_STONE) {
      map_->remove_object(so);
      map_->add_object(new Grass(map_, so->get_x(), so->get_y()));
      map_->get_player()->add_points(POINTS_FOR_STONE);
      break;
    }
    if (player->check_collision_margin(*so, MARGIN)) {
      map_->remove_object(player);
    }
  }

  // UP
  for (int i = 1; i <= power_; i++) {
    so = map_->get_static_object(sx, sy - i);
    if (so == nullptr || so->get_type() == OBJ_WALL) {
      break;
    }

    if (so->get_type() == OBJ_STONE) {
      map_->remove_object(so);
      map_->add_object(new Grass(map_, so->get_x(), so->get_y()));
      map_->get_player()->add_points(POINTS_FOR_STONE);
      break;
    }
    if (player->check_collision_margin(*so, MARGIN)) {
      map_->remove_object(player);
    }
  }

  // DOWN
  for (int i = 1; i <= power_; i++) {
    so = map_->get_static_object(sx, sy + i);
    if (so == nullptr || so->get_type() == OBJ_WALL) {
      break;
    }

    if (so->get_type() == OBJ_STONE) {
      map_->remove_object(so);
      map_->add_object(new Grass(map_, so->get_x(), so->get_y()));
      map_->get_player()->add_points(POINTS_FOR_STONE);
      break;
    }
    
    if (player->check_collision_margin(*so, MARGIN)) {
      map_->remove_object(player);
    }
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
    remove_objects_();
    map_->get_player()->add_bomb();
    map_->remove_object(this);
  }
}

