#include "bullets.h"
#include "raylib.h"

Bullet bullets[MAX_BULLETS] = {0};
float bulletRadius = BULLET_RADIUS;

void InitBullets(void) {
  for (int i = 0; i < MAX_BULLETS; i++) {
    bullets[i] = (Bullet){.position = {0}, .velocity = {0}, .isActive = false};
  }
}
void FireBullet(Vector2 direction, Vector2 position) {
  int idx = -1;
  for (int i = 0; i < MAX_BULLETS; i++) {
    if (!bullets[i].isActive) {
      idx = i;
      break;
    }
  }

  if (idx == -1) {
    return;
  }

  bullets[idx].position = position;
  bullets[idx].velocity =
      (Vector2){direction.x * BULLET_SPEED, direction.y * BULLET_SPEED};
  bullets[idx].isActive = true;
}

void UpdateBullets(float deltaTime) {
  for (int i = 0; i < MAX_BULLETS; i++) {
    bullets[i].position.x += bullets[i].velocity.x * deltaTime;
    bullets[i].position.y += bullets[i].velocity.y * deltaTime;

    if (bullets[i].position.x <= -bulletRadius ||
        bullets[i].position.x >= GetScreenWidth() + bulletRadius ||
        bullets[i].position.y <= -bulletRadius ||
        bullets[i].position.y >= GetScreenHeight() + bulletRadius) {
      bullets[i].isActive = false;
    }
  }
}

void DrawBullets(void) {
  for (int i = 0; i < MAX_BULLETS; i++) {
    if (!bullets[i].isActive) {
      continue;
    }
    DrawCircleV(bullets[i].position, bulletRadius, PURPLE);
  }
}
