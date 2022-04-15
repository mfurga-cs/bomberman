#pragma once

#define PLAYER_INIT_DIRECTION DIRECTION_DOWN
#define PLAYER_INIT_VELOCITY 10

enum Direction {
  DIRECTION_UP = 0,
  DIRECTION_RIGHT,
  DIRECTION_DOWN,
  DIRECTION_LEFT
};

enum ObjectType {
  OBJ_WALL = 0,
  OBJ_STONE,
  OBJ_GRASS,
  OBJ_PLAYER
};

class Object {
 public:
  Object(ObjectType t, int x, int y, int w, int h, SDL_Rect r)
    : t_(t), x_(x), y_(y), w_(w), h_(h), r_(r) {} 


  ObjectType type() {
    return t_;
  }

  int x() const {
    return x_;
  }

  int y() const {
    return y_;
  }

  void render(SDL_Surface *window, SDL_Surface *tiles) {
    SDL_Rect dst = { .x = x_, .y = y_, .w = 48, .h = 48 };
    SDL_BlitSurface(tiles, &r_, window, &dst);
  }

 protected:
  int x_;
  int y_;
  int w_;
  int h_;
  ObjectType t_;
  SDL_Rect r_;
};

class Player: public Object {
 public:
  Player(int x, int y, int w, int h, SDL_Rect r, int v, Direction d)
    : Object(OBJ_PLAYER, x, y, w, h, r), v_(v), d_(d) {}

  Player(int x, int y, int w, int h, SDL_Rect r)
    : Player(x, y, w, h, r, PLAYER_INIT_VELOCITY, PLAYER_INIT_DIRECTION) {}

  void move() {
    switch (d_) {
      case DIRECTION_UP:
        y_ -= 1;
      break;
      case DIRECTION_DOWN:
        y_ += 1;
      break;
      case DIRECTION_LEFT:
        x_ -= 1;
      break;
      case DIRECTION_RIGHT:
        x_ += 1;
      break;
    }
  }

 private:
  int v_;
  Direction d_;
};