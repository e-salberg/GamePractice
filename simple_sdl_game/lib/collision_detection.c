#include <collision_detection.h>

bool check_collision(SDL_FRect entity1, SDL_FRect entity2) {
  bool xOverlap =
      entity1.x + entity1.w >= entity2.x && entity1.x <= entity2.x + entity2.w;
  bool yOverlap =
      entity1.y + entity1.h >= entity2.y && entity1.y <= entity2.y + entity2.h;
  return xOverlap && yOverlap;
}
