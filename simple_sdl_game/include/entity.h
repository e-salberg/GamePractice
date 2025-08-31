#pragma once

#include <SDL3/SDL.h>

#define MAX_ENTITES 100
#define MAX_TAG_LENGTH 64

typedef enum {
  TAG_PLAYER,
  TAG_ENEMY,
} Tag;

typedef struct {
  Tag tag;
  void *data;
  void (*cleanup)(void *data);
  void (*handle_events)(SDL_Event *);
  void (*update)(void *data, float);
  void (*render)(void *data, SDL_Renderer *);
} Entity;

extern Entity entities[];
extern int entities_count;

int create_entity(Entity entity);
int cleanup_all_entities();
int find_entity(Entity entity);
int delete_entity(int index);
