#include "enemy.h"
#include "common.h"
#include "entity.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

static void cleanup(void *data) {
  Enemy *enemy = (Enemy *)data;
  if (enemy) {
    if (enemy->texture) {
      SDL_DestroyTexture(enemy->texture);
    }
    SDL_free(enemy);
  }
}

static void handle_events(SDL_Event *event) {}

static void update(void *data, float dt) {}

static void render(void *data, SDL_Renderer *renderer) {
  Enemy *enemy = (Enemy *)data;
  SDL_SetTextureScaleMode(enemy->texture, SDL_SCALEMODE_NEAREST);
  SDL_RenderTextureRotated(renderer, enemy->texture, NULL, &enemy->rect, 0.0,
                           NULL, enemy->flipTexture);
}

void init_enemy(Vector2 position, SDL_FlipMode direction) {
  char *img_path = NULL;
  Enemy *data = (Enemy *)SDL_malloc(sizeof(Enemy));
  data->flipTexture = direction;

  SDL_asprintf(&img_path, "%simages/cute_cat_enemy.png", SDL_GetBasePath());

  SDL_Renderer *renderer = getRenderer();
  data->texture = IMG_LoadTexture(renderer, img_path);
  if (!data->texture) {
    SDL_Log("Couldn't create static texture for enemy: %s", SDL_GetError());
  }

  data->rect.x = position.x;
  data->rect.y = position.y;
  SDL_GetTextureSize(data->texture, &data->rect.w, &data->rect.h);

  Entity enemy = {
      .tag = TAG_ENEMY,
      .data = data,
      .cleanup = cleanup,
      .handle_events = handle_events,
      .update = update,
      .render = render,
  };
  create_entity(enemy);
}
