#include "asteroids.h"
#include "common.h"
#include "raylib.h"
#include "stdlib.h"

Asteroid asteroids[MAX_ASTEROIDS] = {0};
static Color color = PURPLE;

static int asteroidRadii[3] = {10, 15, 25};

static float lastAsteroidSpwanTime = 0;
static float currentAsteroidDelayTime = 0;

void ResetAsteroids() {
  for (int i = 0; i < MAX_ASTEROIDS; i++) {
    asteroids[i].isActive = false;
  }
}

void SpwanAsteroid() {
  AsteroidSize size = rand() % 3;
  Vector2 position = {0};
  Rectangle possibleTargets = {0, 0, GetScreenWidth(), GetScreenHeight()};
  int side = rand() % 4;
  switch (side) {
  case 0: // top
    position.x =
        rand() % (GetScreenWidth() + asteroidRadii[size]) - asteroidRadii[size];
    position.y = -asteroidRadii[size];
    possibleTargets.x = GetScreenHeight() / 8.f;
    break;
  case 1: // bottom
    position.x =
        rand() % (GetScreenWidth() + asteroidRadii[size]) - asteroidRadii[size];
    position.y = GetScreenHeight() + asteroidRadii[size];
    possibleTargets.height = GetScreenHeight() * 7 / 8.f;
    break;
  case 2: // right
    position.x = GetScreenWidth() + asteroidRadii[size];
    position.y = rand() % (GetScreenHeight() + asteroidRadii[size]) -
                 asteroidRadii[size];
    possibleTargets.width = GetScreenWidth() * 7 / 8.f;
    break;
  default: // left
    position.x = -asteroidRadii[size];
    position.y = rand() % (GetScreenHeight() + asteroidRadii[size]) -
                 asteroidRadii[size];
    possibleTargets.y = GetScreenHeight() / 8.f;
    break;
  }

  Vector2 target = {rand() % (int)possibleTargets.width + possibleTargets.x,
                    rand() % (int)possibleTargets.height + possibleTargets.y};
  Vector2 direction =
      normalize((Vector2){target.x - position.x, target.y - position.y});
  int speed = rand() % ASTEROID_SPEED_MAX + ASTEROID_SPEED_MIN;

  Vector2 velocity = {direction.x * speed, direction.y * speed};

  for (int i = 0; i < MAX_ASTEROIDS; i++) {
    if (!asteroids[i].isActive) {
      asteroids[i].position = position;
      asteroids[i].velocity = velocity;
      asteroids[i].isActive = true;
      asteroids[i].size = size;
      break;
    }
  }
}

void UpdateAsteroids(float deltaTime) {
  for (int i = 0; i < MAX_ASTEROIDS; i++) {
    if (!asteroids[i].isActive) {
      continue;
    }
    asteroids[i].position.x += asteroids[i].velocity.x * deltaTime;
    asteroids[i].position.y += asteroids[i].velocity.y * deltaTime;

    float bufferArea = 2 * asteroidRadii[asteroids[i].size];
    if (asteroids[i].position.x <= -bufferArea ||
        asteroids[i].position.x >= GetScreenWidth() + bufferArea ||
        asteroids[i].position.y <= -bufferArea ||
        asteroids[i].position.y >= GetScreenHeight() + bufferArea) {
      asteroids[i].isActive = false;
    }
  }

  float currentTime = GetTime();
  if (currentTime >= lastAsteroidSpwanTime + currentAsteroidDelayTime) {
    SpwanAsteroid();
    lastAsteroidSpwanTime = currentTime;
    currentAsteroidDelayTime =
        ASTEROID_SPWAN_DELAY_MIN +
        ((float)rand() / RAND_MAX) *
            (ASTEROID_SPWAN_DELAY_MAX - ASTEROID_SPWAN_DELAY_MIN);
  }
}

void DrawAsteroids(void) {
  for (int i = 0; i < MAX_ASTEROIDS; i++) {
    if (!asteroids[i].isActive) {
      continue;
    }
    DrawCircleLinesV(asteroids[i].position, asteroidRadii[asteroids[i].size],
                     color);
  }
}

void DestroyAsteroid(int idx) { asteroids[idx].isActive = false; }

int GetAsteroidRadius(AsteroidSize size) { return asteroidRadii[size]; }
