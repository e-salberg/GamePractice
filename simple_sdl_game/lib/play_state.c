#include "play_state.h"
#include "collision_detection.h"
#include "common.h"
#include "gamestate.h"
#include "player.h"
#include "poop_manager.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_timer.h>

static SDL_Texture *score_text;
static SDL_Color score_color = {255, 255, 255};

static SDL_Texture *time_text;
static SDL_Color time_color = {255, 255, 255};

static uint64_t prev_time = 0;
static float time_remaining;

int score;

static void init() {
  init_player();
  init_poopmanager();

  prev_time = SDL_GetTicks();
  time_remaining = START_TIME;
  score = 0;
}

static void clean_up() {
  cleanup_player();
  cleanup_poopmanager();
}

static SDL_AppResult handle_events(SDL_Event *event) {
  if (event->type == SDL_EVENT_QUIT) {
    return SDL_APP_SUCCESS;
  } else if (event->type == SDL_EVENT_KEY_DOWN &&
             event->key.scancode == SDL_SCANCODE_ESCAPE) {
    return SDL_APP_SUCCESS;
  } else if (event->type == SDL_EVENT_KEY_DOWN &&
             event->key.scancode == SDL_SCANCODE_P) {
    // switch state to end state
    setGameState(END_STATE);
  }
  return SDL_APP_CONTINUE;
}

void handle_collisions(Player *player, Poop_data *data) {
  for (int i = 0; i < data->maxAmount; i++) {
    if (!data->poops[i].isActive) {
      continue;
    }
    SDL_FRect rect;
    rect.x = data->poops[i].position.x;
    rect.y = data->poops[i].position.y;
    rect.h = data->height;
    rect.w = data->width;
    if (check_collision(player->rect, rect)) {
      data->poops[i].isActive = false;
      score += data->point_value;
    }
  }
}

static void update() {
  uint64_t current_time = SDL_GetTicks();
  float dt = (float)(current_time - prev_time);
  update_player(dt);
  updatePoopManager(dt);
  Player *player = get_player();
  Poop_data *rocks = get_rocks();
  Poop_data *potatoes = get_potatoes();

  handle_collisions(player, rocks);
  handle_collisions(player, potatoes);

  time_remaining -= (dt / 1000);
  if (time_remaining <= 0) {
    setGameState(END_STATE);
  }
  prev_time = current_time;
}

static void render(SDL_Renderer *renderer) {
  SDL_RenderClear(renderer);
  render_player(renderer);
  renderPoopManager(renderer);
  SDL_SetRenderDrawColor(renderer, 100, 149, 237, SDL_ALPHA_OPAQUE);

  char score_str[50];
  SDL_snprintf(score_str, sizeof(score_str), "Score:%i", score);
  score_text = getTextTexture(renderer, jetbrains_font, score_str, score_color);
  SDL_FRect dstRect = {20, 20, 250, 100};
  SDL_RenderTexture(renderer, score_text, NULL, &dstRect);

  char time_str[50];
  SDL_snprintf(time_str, sizeof(time_str), "%.2f", time_remaining);
  time_text = getTextTexture(renderer, jetbrains_font, time_str, time_color);
  SDL_FRect timeRect = {WINDOW_WIDTH - 300, 20, 250, 100};
  SDL_RenderTexture(renderer, time_text, NULL, &timeRect);

  SDL_RenderPresent(renderer);
}

void registerPlayState() {
  GameState state = {
      .type = PLAY_STATE,
      .isPaused = false,
      .init = init,
      .clean_up = clean_up,
      .handle_events = handle_events,
      .update = update,
      .render = render,
  };
  registerGameState(state);
}
