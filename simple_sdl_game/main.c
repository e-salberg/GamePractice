#define SDL_MAIN_USE_CALLBACKS 1 /* use callbacks instead of main() */

#include "common.h"
#include "gamestate.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <stdlib.h>
#include <time.h>

static SDL_Window *window;
static SDL_Renderer *renderer;

uint64_t last_frame_time;
TTF_Font *jetbrains_font;

SDL_Renderer *getRenderer() { return renderer; }

// runs once at start up
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
  SDL_SetAppMetadata("Simple Game", "1.0", "example");
  srand(time(NULL));

  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  if (!TTF_Init()) {
    SDL_Log("Couldn't initialize SDL_TTF: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  if (!SDL_CreateWindowAndRenderer("example", WINDOW_WIDTH, WINDOW_HEIGHT, 0,
                                   &window, &renderer)) {
    SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }
  char *font_path = NULL;
  SDL_asprintf(&font_path, "%sfonts/JetBrainsMonoNerdFont-Bold.ttf",
               SDL_GetBasePath());
  jetbrains_font = TTF_OpenFont(font_path, 32);
  if (!jetbrains_font) {
    SDL_Log("failed to load font: %s", SDL_GetError());
  }

  registerAllGameStates();
  setGameState(MAINMENU_STATE);

  last_frame_time = SDL_GetPerformanceCounter();
  return SDL_APP_CONTINUE;
}

// runs when a new event occurs (mouse input, keypress, etc)
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
  return currentState->handle_events(event);
}

// runs once per frame
SDL_AppResult SDL_AppIterate(void *appstate) {
  uint64_t current_frame_time = SDL_GetPerformanceCounter();
  double dt = (double)(current_frame_time - last_frame_time) /
              (double)SDL_GetPerformanceFrequency();
  double fps = 1.0 / dt;
  last_frame_time = current_frame_time;
  // SDL_Log("fps: %lf", fps);

  currentState->update();
  currentState->render(renderer);
  return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
  SDL_DestroyRenderer(renderer);
  renderer = NULL;
  SDL_DestroyWindow(window);
  window = NULL;
  TTF_CloseFont(jetbrains_font);
  TTF_Quit();
  SDL_QuitSubSystem(SDL_INIT_VIDEO);
}
