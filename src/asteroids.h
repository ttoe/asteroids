#pragma once

#include "animation.h"
#include "asteroid.h"
#include "defines.h"

#define ASTEROIDS_MAX 16
#define ASTEROIDS_SPAWN_DELAY 1.5

void asteroids_create(Animation2D *animation, f32 frametime);
i64 asteroids_update(f32 frametime);
void asteroids_draw();
