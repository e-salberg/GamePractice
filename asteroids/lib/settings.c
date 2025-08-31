#include "settings.h"

GameColors colors = {
    .idx = 0,
    .amount = 8,
    .options = {WHITE, LIGHTGRAY, PINK, YELLOW, GREEN, SKYBLUE, PURPLE, BEIGE}};

void CycleColors() {
  colors.idx++;
  if (colors.idx >= colors.amount) {
    colors.idx = 0;
  }
}
