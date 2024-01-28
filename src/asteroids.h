#pragma once

#include "animation.h"
#include "asteroid.h"
#include "defines.h"

#define ASTEROIDS_MAX 16
#define ASTEROIDS_SPAWN_DELAY 1.5

i64 asteroids_update(Animation2D *animation, f32 frametime);
void asteroids_draw();
Asteroid *asteroids_get();
