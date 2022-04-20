#pragma once

struct Context {
  bool key_pressed[1024] = {false};
  int t_now;
  int t_diff;  
};
