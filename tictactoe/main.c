#include "raylib.h"
#include "stdint.h"

#define SCREENWIDTH 800
#define SCREENHEIGHT 450

typedef enum { NONE, X, O } Piece;

Piece board[3][3] = {0};

Rectangle leftLine;
Rectangle rightLine;
Rectangle topLine;
Rectangle botLine;

void update() {}

void draw() {
  BeginDrawing();
  ClearBackground(RAYWHITE);

  int screenWidth = GetScreenWidth();
  int screenHeight = GetScreenHeight();

  leftLine.x = screenWidth / 3.0f;
  leftLine.y = screenHeight / 7.0f;
  leftLine.height = screenHeight * 5 / 7.0f;
  leftLine.width = 5;

  rightLine.x = screenWidth * 2 / 3.0f;
  rightLine.y = screenHeight / 7.0f;
  rightLine.height = screenHeight * 5 / 7.0f;
  rightLine.width = 5;

  topLine.x = screenWidth / 7.0f;
  topLine.y = screenHeight / 3.0f;
  topLine.height = 5;
  topLine.width = screenWidth * 5 / 7.0f;

  botLine.x = screenWidth / 7.0f;
  botLine.y = screenHeight * 2 / 3.0f;
  botLine.height = 5;
  botLine.width = screenWidth * 5 / 7.0f;

  DrawRectangleRec(leftLine, BLACK);
  DrawRectangleRec(rightLine, BLACK);
  DrawRectangleRec(topLine, BLACK);
  DrawRectangleRec(botLine, BLACK);

  EndDrawing();
}

int main(void) {
  InitWindow(SCREENWIDTH, SCREENHEIGHT, "tixtactoe");
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    update();
    draw();
  }

  CloseWindow();
  return 0;
}
