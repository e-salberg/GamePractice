#pragma once

#include <SDL3/SDL.h>

#define PLAYER_MOVESPEED .75f

typedef struct {
  SDL_Texture *texture;
  SDL_FRect rect;
  float move_speed;
  SDL_FlipMode flipTexture;
} Player;

Player *get_player();
void init_player();
void update_player(float dt);
void render_player(SDL_Renderer *renderer);
void cleanup_player();
