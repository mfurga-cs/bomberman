#pragma once

struct Context {
  bool key_pressed[1024] = {false};
  bool end;
  int t_now;
  int t_diff;
  int points;
  const char *message;
};
