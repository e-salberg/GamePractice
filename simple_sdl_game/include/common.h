#pragma once

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 960

typedef struct {
  float x;
  float y;
} Vector2;

extern int score;
extern TTF_Font *jetbrains_font;

void normalize_vector2(Vector2 *v);
SDL_Renderer *getRenderer();
SDL_Texture *getTextTexture(SDL_Renderer *renderer, TTF_Font *font, char *str,
                            SDL_Color color);
void render_outline(SDL_Renderer *renderer, SDL_FRect rect, SDL_Color color);
