#include "entity.h"

Entity entities[MAX_ENTITES];
int entities_count = 0;

int create_entity(Entity entity) {
  if (entities_count >= MAX_ENTITES) {
    SDL_Log("Maximum number of entities already reached: %d", entity.tag);
    return -1;
  }
  entities[entities_count++] = entity;
  return 0;
}

int cleanup_all_entities() {
  while (entities_count > 0) {
    Entity entity = entities[--entities_count];
    entity.cleanup(entity.data);
  }
  return 0;
}

int find_entity(Entity entity) {
  for (int i = 0; i < entities_count; i++) {
    if (entity.data == entities[i].data) {
      return i;
    }
  }
  return -1;
}

int delete_entity(int index) {
  if (index < 0 || index >= entities_count) {
    SDL_Log("Trying to delete an entity but Index was invalid: %d", index);
    return -1;
  }
  Entity entity = entities[index];
  entity.cleanup(entity.data);
  entities_count--;
  for (int i = index; i < entities_count; i++) {
    entities[i] = entities[i + 1];
  }
  return 0;
}
