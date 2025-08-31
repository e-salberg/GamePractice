#pragma once

#include "common.h"
#include <SDL3/SDL.h>

#define MAX_ROCKS 50
#define MAX_POTATOES 50

#define ROCK_WIDTH 50
#define ROCK_HEIGHT 50
#define ROCK_MAX_SPEED .35f
#define ROCK_MIN_SPEED .15f

#define POTATOE_WIDTH 50
#define POTATOE_HEIGHT 69
#define POTATOE_MAX_SPEED .35f
#define POTATOE_MIN_SPEED .15f

typedef struct {
  Vector2 position;
  float speed;
  bool isActive;
  int point_value;
} Poop;

typedef struct {
  Poop poops[50];
  int maxAmount;
  SDL_Texture *texture;
  float width;
  float height;
  int currentIdx;
  int timeToDrop;
  float timeSinceLastDrop;
  float minSpeed;
  float maxSpeed;
  int point_value;
} Poop_data;

Poop_data *get_rocks();
Poop_data *get_potatoes();
void init_poopmanager();
void updatePoopManager(float dt);
void renderPoopManager(SDL_Renderer *renderer);
void cleanup_poopmanager();
