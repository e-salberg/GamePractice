#include "collision.h"
#include "asteroids.h"
#include "bullets.h"
#include "common.h"
#include "player.h"
#include <math.h>

extern float bulletRadius;

bool CheckCircleIntersectsEdge(Vector2 center, float radius, Vector2 v1,
                               Vector2 v2) {
  Vector2 c = {center.x - v1.x, center.y - v1.y};
  Vector2 edge = {v2.x - v1.x, v2.y - v1.y};

  float k = c.x * edge.x + c.y * edge.y;
  if (k > 0) {
    float edgeLength = magnitude(edge);
    k /= edgeLength;
    if (k < edgeLength && sqrtf(c.x * c.x + c.y * c.y - k * k) <= radius) {
      return true;
    }
  }
  return false;
}

// math can be found here: https://www.phatcode.net/articles.php?id=459
bool CheckCollisionAsteroidPlayer(Asteroid asteroid, Triangle player) {
  // check if any triangle vertex is inside circle
  Vector2 distanceV1 = {player.v1.x - asteroid.position.x,
                        player.v1.y - asteroid.position.y};
  Vector2 distanceV2 = {player.v2.x - asteroid.position.x,
                        player.v2.y - asteroid.position.y};
  Vector2 distanceV3 = {player.v3.x - asteroid.position.x,
                        player.v3.y - asteroid.position.y};

  int radius = GetAsteroidRadius(asteroid.size);
  if (magnitude(distanceV1) <= radius || magnitude(distanceV2) <= radius ||
      magnitude(distanceV3) <= radius) {
    return true;
  }

  // Check if circle center is inside of triangle
  if (((player.v2.x - player.v1.x) * (asteroid.position.y - player.v1.y) -
       (player.v2.y - player.v1.y) * (asteroid.position.x - player.v1.x)) >=
          0 &&
      ((player.v3.x - player.v2.x) * (asteroid.position.y - player.v2.y) -
       (player.v3.y - player.v2.y) * (asteroid.position.x - player.v2.x)) >=
          0 &&
      ((player.v1.x - player.v3.x) * (asteroid.position.y - player.v3.y) -
       (player.v1.y - player.v3.y) * (asteroid.position.x - player.v3.x)) >=
          0) {
    return true;
  }

  // Check if circle intersects a triangle edge
  if (CheckCircleIntersectsEdge(asteroid.position, radius, player.v1,
                                player.v2) ||
      CheckCircleIntersectsEdge(asteroid.position, radius, player.v2,
                                player.v3) ||
      CheckCircleIntersectsEdge(asteroid.position, radius, player.v3,
                                player.v1)) {
    return true;
  }
  return false;
}

bool CheckCollisionAsteroidBullet(Asteroid asteroid, Bullet bullet) {
  float dx = bullet.position.x - asteroid.position.x;
  float dy = bullet.position.y - asteroid.position.y;

  float radiiSum = bulletRadius + GetAsteroidRadius(asteroid.size);
  return (dx * dx) + (dy * dy) <= radiiSum * radiiSum;
}
