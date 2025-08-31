#include "ui.h"
#include "raylib.h"
#include "settings.h"

extern int score;
extern int health;
extern GameColors colors;
extern float timer;

void DrawUi(void) {
  DrawText(TextFormat("Health: %i", health), 10, 10, 30,
           colors.options[colors.idx]);
  DrawText(TextFormat("Score: %i", score), 200, 10, 30,
           colors.options[colors.idx]);
  const char *timerText = TextFormat("%.1f", timer);
  DrawText(timerText, GetScreenWidth() / 2 - MeasureText(timerText, 30) / 2, 10,
           30, colors.options[colors.idx]);
}
