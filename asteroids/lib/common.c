#include "common.h"
#include "raylib.h"
#include <math.h>

float magnitude(Vector2 vec) {
  return sqrtf((vec.x * vec.x) + (vec.y * vec.y));
}

Vector2 normalize(Vector2 vec) {
  Vector2 nv = {0};
  float mag = magnitude(vec);
  if (mag) {
    nv.x = vec.x / mag;
    nv.y = vec.y / mag;
  }
  return nv;
}
