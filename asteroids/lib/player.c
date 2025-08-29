#include "player.h"
#include "bullets.h"
#include "common.h"
#include "raylib.h"
#include "settings.h"
#include <math.h>

Triangle player;
int health;
bool isInvulnerable = false;

extern GameColors colors;

static Color invulnerableColor = RED;
static float lastHitTime;
static float lastFireTime;
static float lastInvulnerableFlashTime;
static bool isVisible;

Vector2 getCenter(void);
Vector2 getCurrentDirection(void);
void movePlayer(float deltaTime);
void rotatePlayer(float angle);

void InitPlayer() {
  player = (Triangle){(Vector2){0, 0}, (Vector2){-10, 30}, (Vector2){10, 30}};
  Vector2 center = getCenter();

  player.v1.x += (GetScreenWidth() / 2.f) - center.x;
  player.v1.y += (GetScreenHeight() / 2.f) - center.y;

  player.v2.x += (GetScreenWidth() / 2.f) - center.x;
  player.v2.y += (GetScreenHeight() / 2.f) - center.y;

  player.v3.x += (GetScreenWidth() / 2.f) - center.x;
  player.v3.y += (GetScreenHeight() / 2.f) - center.y;

  isInvulnerable = false;
  health = MAX_HEALTH;
  lastFireTime = -FIRE_RATE;
  lastHitTime = 0.f;
  lastInvulnerableFlashTime = 0.f;
  isVisible = true;
}

void UpdatePlayer(float deltaTime) {
  float currentTime = GetTime();
  if (IsKeyDown(KEY_W)) {
    movePlayer(deltaTime * MOVE_SPEED);
  }
  if (IsKeyDown(KEY_S)) {
    movePlayer(deltaTime * -MOVE_SPEED);
  }
  if (IsKeyDown(KEY_A)) {
    rotatePlayer(deltaTime * -TURN_RATE);
  }
  if (IsKeyDown(KEY_D)) {
    rotatePlayer(deltaTime * TURN_RATE);
  }
  float wrapAdjustmentX = 0;
  if (player.v1.x <= 0 && player.v2.x <= 0 && player.v3.x <= 0) {
    wrapAdjustmentX = GetScreenWidth();
  } else if (player.v1.x >= GetScreenWidth() &&
             player.v2.x >= GetScreenWidth() &&
             player.v3.x >= GetScreenWidth()) {
    wrapAdjustmentX = -GetScreenWidth();
  }
  player.v1.x += wrapAdjustmentX;
  player.v2.x += wrapAdjustmentX;
  player.v3.x += wrapAdjustmentX;

  float wrapAdjustmentY = 0;
  if (player.v1.y <= 0 && player.v2.y <= 0 && player.v3.y <= 0) {
    wrapAdjustmentY = GetScreenHeight();
  } else if (player.v1.y >= GetScreenHeight() &&
             player.v2.y >= GetScreenHeight() &&
             player.v3.y >= GetScreenHeight()) {
    wrapAdjustmentY = -GetScreenHeight();
  }
  player.v1.y += wrapAdjustmentY;
  player.v2.y += wrapAdjustmentY;
  player.v3.y += wrapAdjustmentY;

  if (IsKeyDown(KEY_SPACE) && lastFireTime + FIRE_RATE <= currentTime) {
    FireBullet(getCurrentDirection(), player.v1);
    lastFireTime = currentTime;
  }
  if (isInvulnerable && lastHitTime + INVULNERABLE_TIME <= currentTime) {
    isInvulnerable = false;
    isVisible = true;
  }
  if (isInvulnerable &&
      lastInvulnerableFlashTime + INVULNERABLE_FLASH_INTERVAL <= currentTime) {
    isVisible = !isVisible;
    lastInvulnerableFlashTime = currentTime;
  }
}

void DrawPlayer() {
  if (isVisible) {
    DrawTriangleLines(player.v1, player.v2, player.v3,
                      isInvulnerable ? invulnerableColor
                                     : colors.options[colors.idx]);
  }
}

Vector2 rotatePoint(Vector2 center, Vector2 point, float angle) {
  float translatedX = point.x - center.x;
  float translatedY = point.y - center.y;

  Vector2 rotatedPoint = {translatedX * cosf(angle) - translatedY * sinf(angle),
                          translatedX * sinf(angle) +
                              translatedY * cosf(angle)};

  rotatedPoint.x += center.x;
  rotatedPoint.y += center.y;
  return rotatedPoint;
}

void rotatePlayer(float angle) {
  Vector2 center = {(player.v1.x + player.v2.x + player.v3.x) / 3,
                    (player.v1.y + player.v2.y + player.v3.y) / 3};

  player.v1 = rotatePoint(center, player.v1, angle);
  player.v2 = rotatePoint(center, player.v2, angle);
  player.v3 = rotatePoint(center, player.v3, angle);
}

void movePlayer(float amount) {
  Vector2 direction = getCurrentDirection();

  player.v1 = (Vector2){player.v1.x + direction.x * amount,
                        player.v1.y + direction.y * amount};
  player.v2 = (Vector2){player.v2.x + direction.x * amount,
                        player.v2.y + direction.y * amount};
  player.v3 = (Vector2){player.v3.x + direction.x * amount,
                        player.v3.y + direction.y * amount};
}

void playerTakeDamage() {
  if (isInvulnerable) {
    return;
  }
  isInvulnerable = true;
  lastHitTime = GetTime();
  health--;
}

Vector2 getCurrentDirection() {
  Vector2 center = getCenter();
  return normalize((Vector2){player.v1.x - center.x, player.v1.y - center.y});
}

Vector2 getCenter() {
  return (Vector2){(player.v1.x + player.v2.x + player.v3.x) / 3,
                   (player.v1.y + player.v2.y + player.v3.y) / 3};
}
