#pragma once

#include <SDL3/SDL.h>

#define MAX_STATES 10

typedef enum {
  NO_STATE = -1,
  MAINMENU_STATE,
  PLAY_STATE,
  END_STATE,
} State_Type;

typedef struct {
  State_Type type;
  bool isPaused;
  void (*init)();
  void (*clean_up)();
  SDL_AppResult (*handle_events)(SDL_Event *);
  void (*update)();
  void (*render)(SDL_Renderer *);
} GameState;

extern GameState gameStates[];
extern int states_count;
extern GameState *currentState;

void registerAllGameStates();
void registerGameState(GameState state);
void setGameState(State_Type type);
