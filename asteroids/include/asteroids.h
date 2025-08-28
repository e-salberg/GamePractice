#pragma once

#include "raylib.h"

#define MAX_ASTEROIDS 100
#define ASTEROID_SPEED_MAX 225
#define ASTEROID_SPEED_MIN 100
#define ASTEROID_SPWAN_DELAY_MAX 2.25f
#define ASTEROID_SPWAN_DELAY_MIN 0.f

typedef enum { SMALL, MEDIUM, LARGE } AsteroidSize;

typedef struct {
  AsteroidSize size;
  Vector2 position;
  Vector2 velocity;
  bool isActive;
} Asteroid;

void ResetAsteroids(void);
void SpwanAsteroid(void);
void UpdateAsteroids(float deltaTime);
void DrawAsteroids(void);
void DestroyAsteroid(int idx);
int GetAsteroidRadius(AsteroidSize size);
