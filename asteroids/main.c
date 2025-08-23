#include "player.h"
#include <raylib.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450

static Triangle player;

void Update(void);
void UpdatePlayer(float deltaTime);
void Draw(void);

int main() {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "asteroids");

  player = (Triangle){
      (Vector2){SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f},
      (Vector2){(SCREEN_WIDTH / 2.f) - 10, (SCREEN_HEIGHT / 2.f) + 30},
      (Vector2){(SCREEN_WIDTH / 2.f) + 10, (SCREEN_HEIGHT / 2.f) + 30}};

  while (!WindowShouldClose()) {
    Update();
    Draw();
  }
}

void Update() {
  float deltaTime = GetFrameTime();
  UpdatePlayer(deltaTime);
}

void UpdatePlayer(float deltaTime) {
  if (IsKeyDown(KEY_W)) {
    MovePlayer(&player, deltaTime * MOVE_SPEED);
  }
  if (IsKeyDown(KEY_S)) {
    MovePlayer(&player, -1 * deltaTime * MOVE_SPEED);
  }
  if (IsKeyDown(KEY_A)) {
    RotatePlayer(&player, -1 * deltaTime * TURN_RATE);
  }
  if (IsKeyDown(KEY_D)) {
    RotatePlayer(&player, deltaTime * TURN_RATE);
  }
}

void Draw() {
  BeginDrawing();
  ClearBackground(BLACK);

  DrawTriangleLines(player.v1, player.v2, player.v3, PURPLE);

  Vector2 center = {(player.v1.x + player.v2.x + player.v3.x) / 3.f,
                    (player.v1.y + player.v2.y + player.v3.y) / 3.f};
  DrawPixelV(center, PURPLE);

  EndDrawing();
}
