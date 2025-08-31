#include "player.h"
#include "common.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

static Player *player;

Player *get_player() { return player; }

void cleanup_player() {
  if (player) {
    if (player->texture) {
      SDL_DestroyTexture(player->texture);
    }
    SDL_free(player);
  }
}

void update_player(float dt) {
  const bool *keyboard_state = SDL_GetKeyboardState(NULL);
  Vector2 velocity = {0, 0};
  velocity.y = keyboard_state[SDL_SCANCODE_S] - keyboard_state[SDL_SCANCODE_W];
  velocity.x = keyboard_state[SDL_SCANCODE_D] - keyboard_state[SDL_SCANCODE_A];
  normalize_vector2(&velocity);

  float new_x_position = (velocity.x * player->move_speed * dt);
  player->rect.x += new_x_position;
  if (player->rect.x <= 0 ||
      player->rect.x >= WINDOW_WIDTH - player->texture->w) {
    player->rect.x -= new_x_position;
  }

  float new_y_position = (velocity.y * player->move_speed * dt);
  player->rect.y += new_y_position;
  if (player->rect.y <= 0 ||
      player->rect.y >= WINDOW_HEIGHT - player->texture->h) {
    player->rect.y -= new_y_position;
  }

  if (velocity.x > 0) {
    player->flipTexture = SDL_FLIP_NONE;
  } else if (velocity.x < 0) {
    player->flipTexture = SDL_FLIP_HORIZONTAL;
  }
}

void render_player(SDL_Renderer *renderer) {
  SDL_SetTextureScaleMode(player->texture, SDL_SCALEMODE_NEAREST);
  SDL_RenderTextureRotated(renderer, player->texture, NULL, &player->rect, 0.0,
                           NULL, player->flipTexture);
  SDL_Color red = {.r = 255, .g = 0, .b = 0, .a = SDL_ALPHA_OPAQUE};
  render_outline(renderer, player->rect, red);
}

void init_player() {
  char *img_path = NULL;
  player = (Player *)SDL_malloc(sizeof(Player));

  SDL_asprintf(&img_path, "%simages/cute_cat_chicken.bmp", SDL_GetBasePath());

  SDL_Renderer *renderer = getRenderer();
  player->texture = IMG_LoadTexture(renderer, img_path);
  if (!player->texture) {
    SDL_Log("Couldn't create static texture for player: %s", SDL_GetError());
  }

  player->rect.x = (WINDOW_WIDTH - player->texture->w) / 2.0f;
  player->rect.y = (WINDOW_HEIGHT - player->texture->h);
  SDL_GetTextureSize(player->texture, &player->rect.w, &player->rect.h);
  player->move_speed = PLAYER_MOVESPEED;
}
