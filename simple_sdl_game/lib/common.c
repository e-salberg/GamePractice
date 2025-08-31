#include <common.h>
#include <math.h>

// #define MAGNITUDE(x, y) sqrtf((x * x) + (y * y))

void normalize_vector2(Vector2 *vector) {
  float magnitude = sqrtf((vector->x * vector->x) + (vector->y * vector->y));
  if (magnitude) {
    vector->x = vector->x / magnitude;
    vector->y = vector->y / magnitude;
  }
}

SDL_Texture *getTextTexture(SDL_Renderer *renderer, TTF_Font *font, char *str,
                            SDL_Color color) {
  SDL_Surface *surface = TTF_RenderText_Blended(font, str, 0, color);
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_DestroySurface(surface);
  return texture;
}

void render_outline(SDL_Renderer *renderer, SDL_FRect rect, SDL_Color color) {
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

  Vector2 topLeft = {rect.x, rect.y};
  Vector2 botLeft = {rect.x, rect.y + rect.h};
  Vector2 topRight = {rect.x + rect.w, rect.y};
  Vector2 botRight = {rect.x + rect.w, rect.y + rect.h};

  SDL_RenderLine(renderer, topLeft.x, topLeft.y, botLeft.x, botLeft.y);
  SDL_RenderLine(renderer, topLeft.x, topLeft.y, topRight.x, topRight.y);
  SDL_RenderLine(renderer, botLeft.x, botLeft.y, botRight.x, botRight.y);
  SDL_RenderLine(renderer, topRight.x, topRight.y, botRight.x, botRight.y);
}
