#pragma once

#include "animation.h"
#include "player.h"
#include "projectile.h"

#define PROJECTILES_MAX 16

void projectiles_create(Animation2D *animation, Player *player, f32 frametime);
i64 projectiles_update(f32 frametime);
void projectiles_draw();
void projectiles_collide(Asteroid *asteroids);
