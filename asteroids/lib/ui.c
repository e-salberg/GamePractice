#include "ui.h"
#include "raylib.h"
#include "settings.h"

extern int score;
extern int health;
extern GameColors colors;

void DrawUi(void) {
  DrawText(TextFormat("Health: %i", health), GetScreenWidth() / 6, 10, 30,
           colors.options[colors.idx]);

  DrawText(TextFormat("Score: %i", score), GetScreenWidth() / 3, 10, 30,
           colors.options[colors.idx]);
}
