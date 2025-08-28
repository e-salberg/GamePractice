#include "asteroids.h"
#include "bullets.h"
#include "collision.h"
#include "player.h"
#include "raylib.h"
#include "stdlib.h"
#include "time.h"

typedef enum { PLAY, GAMEOVER } State;

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define GAMEOVER_FONT_SIZE 80

State state = PLAY;
char *gameoverText = "GAME OVER";

extern Triangle player;
extern int health;
extern bool isInvulnerable;
extern Asteroid asteroids[];
extern Bullet bullets[];

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
        if (CheckCollisionAsteroidBullet(asteroids[i], bullets[j])) {
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
    if (IsKeyDown(KEY_ENTER)) {
      InitPlayer();
      InitBullets();
      ResetAsteroids();
      state = PLAY;
    }
    break;
  }
}

void Draw() {
  BeginDrawing();
  ClearBackground(BLACK);
  switch (state) {
  case PLAY:
    DrawPlayer();
    DrawBullets();
    DrawAsteroids();
    break;
  case GAMEOVER:
    DrawText(gameoverText,
             (GetScreenWidth() / 2) -
                 (MeasureText(gameoverText, GAMEOVER_FONT_SIZE) / 2),
             (GetScreenHeight() / 2) - GAMEOVER_FONT_SIZE / 2,
             GAMEOVER_FONT_SIZE, RED);
    break;
  }
  DrawFPS(10, 10);
  EndDrawing();
}
