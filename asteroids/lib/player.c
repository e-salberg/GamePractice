#include "player.h"
#include "math.h"
#include "raylib.h"

Vector2 normalize(Vector2 vec) {
  Vector2 nv = {0};
  float mag = sqrtf((vec.x * vec.x) + (vec.y * vec.y));
  if (mag) {
    nv.x = vec.x / mag;
    nv.y = vec.y / mag;
  }
  return nv;
}

Vector2 RotatePoint(Vector2 center, Vector2 point, float angle) {
  float translatedX = point.x - center.x;
  float translatedY = point.y - center.y;

  Vector2 rotatedPoint = {translatedX * cosf(angle) - translatedY * sinf(angle),
                          translatedX * sinf(angle) +
                              translatedY * cosf(angle)};

  rotatedPoint.x += center.x;
  rotatedPoint.y += center.y;
  return rotatedPoint;
}

void RotatePlayer(Triangle *player, float angle) {
  Vector2 center = {(player->v1.x + player->v2.x + player->v3.x) / 3.f,
                    (player->v1.y + player->v2.y + player->v3.y) / 3.f};

  player->v1 = RotatePoint(center, player->v1, angle);
  player->v2 = RotatePoint(center, player->v2, angle);
  player->v3 = RotatePoint(center, player->v3, angle);
}

Vector2 MovePoint(Vector2 point, Vector2 direction, float deltaTime) {
  Vector2 translated_point =
      (Vector2){point.x + direction.x * deltaTime * MOVE_SPEED,
                point.y + direction.y * deltaTime * MOVE_SPEED};
  return translated_point;
}

void MovePlayer(Triangle *player, float deltaTime) {
  Vector2 center = {(player->v1.x + player->v2.x + player->v3.x) / 3.f,
                    (player->v1.y + player->v2.y + player->v3.y) / 3.f};

  Vector2 direction =
      normalize((Vector2){player->v1.x - center.x, player->v1.y - center.y});

  player->v1 = MovePoint(player->v1, direction, deltaTime);
  player->v2 = MovePoint(player->v2, direction, deltaTime);
  player->v3 = MovePoint(player->v3, direction, deltaTime);
}
