#pragma once

#include "raylib.h"

#define TURN_RATE 2.5f
#define MOVE_SPEED 10.f

typedef struct {
  Vector2 v1;
  Vector2 v2;
  Vector2 v3;
} Triangle;

void RotatePlayer(Triangle *player, float angle);
void MovePlayer(Triangle *player, float deltaTime);
