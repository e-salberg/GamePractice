#pragma once

#include "raylib.h"

#define FIRE_RATE 0.5f
#define TURN_RATE 2.5f
#define MOVE_SPEED 150.f
#define INVULNERABLE_TIME 3.f
#define INVULNERABLE_FLASH_INTERVAL .15f
#define MAX_HEALTH 3

typedef struct {
  Vector2 v1;
  Vector2 v2;
  Vector2 v3;
} Triangle;

void InitPlayer(void);
void UpdatePlayer(float deltaTime);
void DrawPlayer(void);
void playerTakeDamage();
