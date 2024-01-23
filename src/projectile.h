#pragma once

#include "animation.h"
#include "player.h"
#include "raylib.h"

#define PROJECTILE_PLAYER_OFFSET 30
#define PROJECTILE_RELOAD_TIME 0.2f
#define PROJECTILE_SPEED 700

typedef struct Projectile
{
    Vector2 position;
    Vector2 velocity;

    bool is_active;
} Projectile;

Projectile projectile_init(Animation2D *animation, Player *player);
i64 projectile_update(Projectile *projectile, f32 frametime);
void projectile_draw(Projectile projectile);
