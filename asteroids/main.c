#include "asteroids.h"
#include "bullets.h"
#include "collision.h"
#include "player.h"
#include "raylib.h"
#include "settings.h"
#include "stdlib.h"
#include "time.h"
#include "ui.h"

typedef enum { TITLE, CONTROLS, PLAY, GAMEOVER } State;

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define START_TIME 100
#define GAMEOVER_FONT_SIZE 100
#define TITLE_FONT_SIZE 100
#define CONTROLS_FONT_SIZE 50

State state = TITLE;
char *gameoverText = "GAME OVER";
char *titleText = "SPACE ROCKS";

int points[3] = {100, 50, 20};
int score = 0;
float timer = START_TIME;

extern Triangle player;
extern int health;
extern bool isInvulnerable;
extern Asteroid asteroids[];
extern Bullet bullets[];
extern GameColors colors;

void Update(void);
void Draw(void);

int main() {
  srand(time(NULL));
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "asteroids");
  InitPlayer();
  InitBullets();

  while (!WindowShouldClose()) {
    Update();
    Draw();
  }
  CloseWindow();
}

void Update() {
  if (IsKeyPressed(KEY_Q)) {
    CycleColors();
  }

  float deltaTime = GetFrameTime();
  switch (state) {
  case TITLE:
    if (IsKeyPressed(KEY_ENTER)) {
      state = CONTROLS;
    }
    break;
  case CONTROLS:
    if (IsKeyPressed(KEY_ENTER)) {
      InitPlayer();
      InitBullets();
      ResetAsteroids();
      score = 0;
      state = PLAY;
      timer = START_TIME;
    }
    break;
  case PLAY:
    UpdatePlayer(deltaTime);
    UpdateBullets(deltaTime);
    UpdateAsteroids(deltaTime);

    for (int i = 0; i < MAX_ASTEROIDS; i++) {
      if (!asteroids[i].isActive) {
        continue;
      }
      if (!isInvulnerable &&
          CheckCollisionAsteroidPlayer(asteroids[i], player)) {
        playerTakeDamage();
      }

      for (int j = 0; j < MAX_BULLETS; j++) {
        if (!bullets[j].isActive) {
          continue;
        }
        if (CheckCollisionAsteroidBullet(asteroids[i], bullets[j])) {
          score += points[asteroids[i].size];
          DestroyAsteroid(i);
          break;
        }
      }
    }

    timer -= deltaTime;
    if (timer <= 0) {
      timer = 0;
      state = GAMEOVER;
    }
    if (health <= 0) {
      state = GAMEOVER;
    }
    break;
  case GAMEOVER:
    if (IsKeyPressed(KEY_ENTER)) {
      InitPlayer();
      InitBullets();
      ResetAsteroids();
      score = 0;
      state = PLAY;
      timer = START_TIME;
    }
    break;
  }
}

void Draw() {
  BeginDrawing();
  ClearBackground(BLACK);
  switch (state) {
  case TITLE:
    DrawText(titleText,
             GetScreenWidth() / 2 -
                 (MeasureText(titleText, TITLE_FONT_SIZE) / 2),
             GetScreenHeight() / 2 - TITLE_FONT_SIZE, TITLE_FONT_SIZE,
             colors.options[colors.idx]);
    char *start = "Press Enter to start";
    DrawText(start,
             GetScreenWidth() / 2 - MeasureText(start, TITLE_FONT_SIZE / 2) / 2,
             GetScreenHeight() / 2 + 50, TITLE_FONT_SIZE / 2,
             colors.options[colors.idx]);
    break;
  case CONTROLS: {
    char *start = "Press Enter to start";
    DrawText(start,
             GetScreenWidth() / 2 -
                 MeasureText(start, CONTROLS_FONT_SIZE + 20) / 2,
             GetScreenHeight() / 6, CONTROLS_FONT_SIZE + 20,
             colors.options[colors.idx]);
    char *move = "W/S - move forward/backwards";
    DrawText(move,
             GetScreenWidth() / 2 - MeasureText(move, CONTROLS_FONT_SIZE) / 2,
             225, CONTROLS_FONT_SIZE, colors.options[colors.idx]);
    char *rotate = "A/D - rotate left/right";
    DrawText(rotate,
             GetScreenWidth() / 2 - MeasureText(rotate, CONTROLS_FONT_SIZE) / 2,
             325, CONTROLS_FONT_SIZE, colors.options[colors.idx]);
    char *shoot = "SPACE - shoot bullet";
    DrawText(shoot,
             GetScreenWidth() / 2 - MeasureText(shoot, CONTROLS_FONT_SIZE) / 2,
             425, CONTROLS_FONT_SIZE, colors.options[colors.idx]);
    char *cycleColor = "Q - Cycle through colors";
    DrawText(cycleColor,
             GetScreenWidth() / 2 -
                 MeasureText(cycleColor, CONTROLS_FONT_SIZE) / 2,
             525, CONTROLS_FONT_SIZE, colors.options[colors.idx]);
  } break;
  case PLAY:
    DrawPlayer();
    DrawBullets();
    DrawAsteroids();
    DrawUi();
    break;
  case GAMEOVER: {
    DrawText(gameoverText,
             GetScreenWidth() / 2 -
                 MeasureText(gameoverText, GAMEOVER_FONT_SIZE) / 2,
             GetScreenHeight() / 2 - GAMEOVER_FONT_SIZE, GAMEOVER_FONT_SIZE,
             colors.options[colors.idx]);
    char *restart = "Press Enter to Try Again";
    DrawText(restart,
             GetScreenWidth() / 2 -
                 MeasureText(restart, GAMEOVER_FONT_SIZE / 2) / 2,
             GetScreenHeight() / 2 + 50, GAMEOVER_FONT_SIZE / 2,
             colors.options[colors.idx]);
    DrawUi();
  } break;
  }
  EndDrawing();
}
