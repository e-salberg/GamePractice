#pragma once
#include "raylib.h"

#define MAX_BULLETS 20
#define BULLET_SPEED 300.f
#define BULLET_RADIUS 2.5f

typedef struct {
  Vector2 position;
  Vector2 velocity;
  bool isActive;
} Bullet;

void InitBullets(void);
void FireBullet(Vector2 direction, Vector2 position);
void UpdateBullets(float deltaTime);
void DrawBullets(void);
