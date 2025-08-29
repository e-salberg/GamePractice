#pragma once

#include "raylib.h"

typedef struct {
  int idx;
  int amount;
  Color options[];
} GameColors;

void ToggleColors(void);
