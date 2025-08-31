#include "poop_manager.h"
#include "common.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>
#include <SDL3_image/SDL_image.h>
#include <stdlib.h>

static Poop_data rocks = {.maxAmount = MAX_ROCKS,
                          .width = ROCK_WIDTH,
                          .height = ROCK_HEIGHT,
                          .timeToDrop = 0,
                          .timeSinceLastDrop = 0,
                          .minSpeed = ROCK_MIN_SPEED,
                          .maxSpeed = ROCK_MAX_SPEED};

static Poop_data potatoes = {.maxAmount = MAX_POTATOES,
                             .width = POTATOE_WIDTH,
                             .height = POTATOE_HEIGHT,
                             .timeToDrop = 0,
                             .timeSinceLastDrop = 0,
                             .minSpeed = POTATOE_MIN_SPEED,
                             .maxSpeed = POTATOE_MAX_SPEED};

Poop_data *get_rocks() { return &rocks; }
Poop_data *get_potatoes() { return &potatoes; }

float getRandomPositionX(int poop_width) {
  return rand() % (WINDOW_WIDTH - poop_width);
}

float getRandomSpeed(float min, float max) {
  return min + (((float)rand() / RAND_MAX) * (max - min));
}

int getRandomTimeToDrop() {
  return (rand() % 500) + (rand() % 500) + (rand() % 500);
}

void reset_poop(Poop_data *data) {
  for (int i = 0; i < data->maxAmount; i++) {
    data->poops[i].isActive = false;
  }
}

void init_poopmanager() {
  char *rock_img_path = NULL;
  SDL_asprintf(&rock_img_path, "%simages/rock.png", SDL_GetBasePath());
  rocks.texture = IMG_LoadTexture(getRenderer(), rock_img_path);

  reset_poop(&rocks);
  rocks.currentIdx = 1;
  rocks.timeSinceLastDrop = 0;
  rocks.timeToDrop = 0;
  rocks.poops[0].isActive = true;
  rocks.poops[0].position.x = getRandomPositionX(ROCK_WIDTH);
  rocks.poops[0].position.y = -ROCK_HEIGHT;
  rocks.poops[0].speed = getRandomSpeed(ROCK_MIN_SPEED, ROCK_MAX_SPEED);
  rocks.point_value = -1;

  char *potatoe_img_path = NULL;
  SDL_asprintf(&potatoe_img_path, "%simages/potato.png", SDL_GetBasePath());
  potatoes.texture = IMG_LoadTexture(getRenderer(), potatoe_img_path);

  reset_poop(&potatoes);
  potatoes.currentIdx = 1;
  potatoes.timeSinceLastDrop = 0;
  potatoes.timeToDrop = 0;
  potatoes.poops[0].isActive = true;
  potatoes.poops[0].position.x = getRandomPositionX(POTATOE_WIDTH);
  potatoes.poops[0].position.y = -POTATOE_HEIGHT;
  potatoes.poops[0].speed =
      getRandomSpeed(POTATOE_MIN_SPEED, POTATOE_MAX_SPEED);
  potatoes.point_value = 1;
}

void updatePoop(Poop_data *data, float dt) {
  if (data->timeSinceLastDrop > data->timeToDrop &&
      !data->poops[data->currentIdx].isActive) {
    data->poops[data->currentIdx].isActive = true;
    data->poops[data->currentIdx].speed =
        getRandomSpeed(data->minSpeed, data->maxSpeed);
    data->poops[data->currentIdx].position.y = -data->height;
    data->poops[data->currentIdx].position.x = getRandomPositionX(data->width);
    data->currentIdx++;
    if (data->currentIdx >= data->maxAmount) {
      data->currentIdx = 0;
    }
    data->timeSinceLastDrop = 0;
    data->timeToDrop = getRandomTimeToDrop();
  } else {
    data->timeSinceLastDrop += dt;
  }

  for (int i = 0; i < data->maxAmount; i++) {
    if (!data->poops[i].isActive) {
      continue;
    }
    data->poops[i].position.y += data->poops[i].speed * dt;

    if (data->poops[i].position.y > WINDOW_HEIGHT) {
      data->poops[i].isActive = false;
    }
  }
}

void updatePoopManager(float dt) {
  updatePoop(&rocks, dt);
  updatePoop(&potatoes, dt);
}

void renderPoop(SDL_Renderer *renderer, Poop_data data, SDL_Color color) {
  SDL_FRect rect;
  for (int i = 0; i < data.maxAmount; i++) {
    if (!data.poops[i].isActive) {
      continue;
    }
    SDL_SetTextureScaleMode(data.texture, SDL_SCALEMODE_NEAREST);
    rect.x = data.poops[i].position.x;
    rect.y = data.poops[i].position.y;
    rect.h = data.height;
    rect.w = data.width;
    SDL_RenderTexture(renderer, data.texture, NULL, &rect);
    render_outline(renderer, rect, color);
  }
}

void renderPoopManager(SDL_Renderer *renderer) {
  SDL_Color blue = {.r = 0, .g = 0, .b = 255, .a = SDL_ALPHA_OPAQUE};
  SDL_Color green = {.r = 0, .g = 255, .b = 0, .a = SDL_ALPHA_OPAQUE};
  renderPoop(renderer, rocks, blue);
  renderPoop(renderer, potatoes, green);
}

void cleanup_poopmanager() {
  if (rocks.texture) {
    SDL_DestroyTexture(rocks.texture);
  }
  if (potatoes.texture) {
    SDL_DestroyTexture(potatoes.texture);
  }
}
