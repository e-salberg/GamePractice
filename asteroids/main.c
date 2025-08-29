#include "asteroids.h"
#include "bullets.h"
#include "collision.h"
#include "player.h"
#include "raylib.h"
#include "settings.h"
#include "stdlib.h"
#include "time.h"
#include "ui.h"

typedef enum { TITLE, PLAY, GAMEOVER } State;

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define START_TIME 100
#define GAMEOVER_FONT_SIZE 80
#define TITLE_FONT_SIZE 100

State state = TITLE;
char *gameoverText = "GAME OVER";
char *titleText = "SPACE ROCKS";

int points[3] = {100, 50, 20};
int score = 0;
int timer;

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
  float deltaTime = GetFrameTime();
  switch (state) {
  case TITLE:
    if (IsKeyDown(KEY_ENTER)) {
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

  if (IsKeyPressed(KEY_TAB)) {
    ToggleColors();
  }
}

void Draw() {
  BeginDrawing();
  ClearBackground(BLACK);
  switch (state) {
  case TITLE:
    DrawText(titleText,
             (GetScreenWidth() / 2) -
                 (MeasureText(titleText, TITLE_FONT_SIZE) / 2),
             (GetScreenHeight() / 2) - TITLE_FONT_SIZE / 2, TITLE_FONT_SIZE,
             colors.options[colors.idx]);
    break;
  case PLAY:
    DrawPlayer();
    DrawBullets();
    DrawAsteroids();
    DrawUi();
    break;
  case GAMEOVER:
    DrawText(gameoverText,
             (GetScreenWidth() / 2) -
                 (MeasureText(gameoverText, GAMEOVER_FONT_SIZE) / 2),
             (GetScreenHeight() / 2) - GAMEOVER_FONT_SIZE / 2,
             GAMEOVER_FONT_SIZE, colors.options[colors.idx]);
    DrawUi();
    break;
  }
  DrawFPS(10, 10);
  EndDrawing();
}
