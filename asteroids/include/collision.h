#pragma once

#include "asteroids.h"
#include "bullets.h"
#include "player.h"
#include "stdbool.h"

bool CheckCollisionAsteroidPlayer(Asteroid asteroid, Triangle player);
bool CheckCollisionAsteroidBullet(Asteroid asteroid, Bullet bullet);
