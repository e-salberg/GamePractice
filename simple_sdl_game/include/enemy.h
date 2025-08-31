#pragma once

#include <SDL3/SDL.h>
#include <common.h>

typedef struct {
  SDL_Texture *texture;
  SDL_FRect rect;
  SDL_FlipMode flipTexture;
} Enemy;

void init_enemy(Vector2 position, SDL_FlipMode direction);
