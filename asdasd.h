#pragma once

enum ObjectType {
  OBJ_WALL = 0,
  OBJ_STONE,
  OBJ_GRASS,
  OBJ_PLAYER
};

class Object {
 public:
  Object(int x, int y, int w, int h, SDL_Rect r)
    : t_(t), x_(x), y_(y), w_(w), h_(h), r_(r) {} 

  int get_x() const { return x_; }

  int get_y() const { return y_; }

  virtual ObjectType get_type();
  virtual void render();

 protected:
  int x_;
  int y_;
  int w_;
  int h_;
  ObjectType type_;
};


#define PLAYER_INIT_DIRECTION DIRECTION_DOWN
#define PLAYER_INIT_VELOCITY 10

enum Direction {
  DIRECTION_UP = 0,
  DIRECTION_RIGHT,
  DIRECTION_DOWN,
  DIRECTION_LEFT
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