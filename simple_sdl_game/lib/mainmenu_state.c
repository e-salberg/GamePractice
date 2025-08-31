#include "mainmenu_state.h"
#include "common.h"
#include "gamestate.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_surface.h>
#include <SDL3_ttf/SDL_ttf.h>

#define PRESS_BUTTONS_TEXT_HEIGHT 100
#define PRESS_BUTTONS_TEXT_WIDTH 700

static SDL_Texture *mainmenu_text;
static SDL_Texture *press_buttons_text;
static SDL_Color text_color = {255, 255, 255};

static void init() {
  SDL_Renderer *renderer = getRenderer();
  mainmenu_text =
      getTextTexture(renderer, jetbrains_font, "Main Menu", text_color);
  press_buttons_text = getTextTexture(
      renderer, jetbrains_font, "Press Any Button to Start...", text_color);
}

static void clean_up() {}

static SDL_AppResult handle_events(SDL_Event *event) {
  if (event->type == SDL_EVENT_QUIT) {
    return SDL_APP_SUCCESS;
  } else if (event->type == SDL_EVENT_KEY_DOWN &&
             event->key.scancode == SDL_SCANCODE_ESCAPE) {
    return SDL_APP_SUCCESS;
  } else if (event->type == SDL_EVENT_KEY_DOWN) {
    // switch state to play state
    setGameState(PLAY_STATE);
  }
  return SDL_APP_CONTINUE;
}

static void update() {}

static void render(SDL_Renderer *renderer) {
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 128, 112, 181, SDL_ALPHA_OPAQUE);

  SDL_FRect dstRect = {20, 20, 500, 100};
  SDL_RenderTexture(renderer, mainmenu_text, NULL, &dstRect);

  dstRect.x = (float)(WINDOW_WIDTH - PRESS_BUTTONS_TEXT_WIDTH) / 2.0f;
  dstRect.y = (float)(WINDOW_HEIGHT - PRESS_BUTTONS_TEXT_HEIGHT) / 2.0f;
  dstRect.w = PRESS_BUTTONS_TEXT_WIDTH;
  dstRect.h = PRESS_BUTTONS_TEXT_HEIGHT;
  const double now = (double)SDL_GetTicks();
  const float alpha = (float)(.7 + .7 * SDL_sin(now * .003));
  SDL_SetTextureAlphaModFloat(press_buttons_text, alpha);
  SDL_RenderTexture(renderer, press_buttons_text, NULL, &dstRect);

  SDL_RenderPresent(renderer);
}

void registerMainMenu() {
  GameState state = {
      .type = MAINMENU_STATE,
      .isPaused = false,
      .init = init,
      .clean_up = clean_up,
      .handle_events = handle_events,
      .update = update,
      .render = render,
  };
  registerGameState(state);
}
