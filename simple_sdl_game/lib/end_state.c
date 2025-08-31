#include "end_state.h"
#include "common.h"
#include "gamestate.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_stdinc.h>

static SDL_Texture *score_text;
static SDL_Color score_color = {255, 255, 255};

static void init() {
  char score_str[50];
  SDL_snprintf(score_str, sizeof(score_str), "Final Score was:%i", score);
  score_text =
      getTextTexture(getRenderer(), jetbrains_font, score_str, score_color);
}

static SDL_AppResult handle_events(SDL_Event *event) {
  if (event->type == SDL_EVENT_QUIT) {
    return SDL_APP_SUCCESS;
  } else if (event->type == SDL_EVENT_KEY_DOWN &&
             event->key.scancode == SDL_SCANCODE_ESCAPE) {
    return SDL_APP_SUCCESS;
  } else if (event->type == SDL_EVENT_KEY_DOWN &&
             event->key.scancode == SDL_SCANCODE_R) {
    // restart game?
    setGameState(MAINMENU_STATE);
  }
  return SDL_APP_CONTINUE;
}

static void update() {}

static void render(SDL_Renderer *renderer) {
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

  SDL_FRect dstRect = {20, 20, 500, 100};
  SDL_RenderTexture(renderer, score_text, NULL, &dstRect);
  SDL_RenderPresent(renderer);
}

void registerEndState() {
  GameState state = {
      .type = END_STATE,
      .init = init,
      .handle_events = handle_events,
      .update = update,
      .render = render,
  };
  registerGameState(state);
}
