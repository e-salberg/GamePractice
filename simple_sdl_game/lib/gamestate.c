#include "gamestate.h"
#include "end_state.h"
#include "mainmenu_state.h"
#include "play_state.h"

GameState gameStates[MAX_STATES];
int states_count = 0;
GameState *currentState;

void registerAllGameStates() {
  registerMainMenu();
  registerPlayState();
  registerEndState();
}

void registerGameState(GameState state) {
  if (states_count >= MAX_STATES) {
    SDL_Log("Maximum number of states already have been registered");
    return;
  }

  if (state.type == NO_STATE) {
    SDL_Log("Trying to register an invalid game state");
    return;
  }
  gameStates[state.type] = state;
}

void setGameState(State_Type type) {
  GameState *oldState = currentState;
  currentState = &gameStates[type];
  if (currentState->init) {
    currentState->init();
  }

  if (oldState != NULL && oldState->clean_up != NULL) {
    oldState->clean_up();
  }
}
