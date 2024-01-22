#pragma once

#include "animation.h"
#include "defines.h"
#include "raylib.h"

#define ASTEROID_SPAWN_PADDING 30
#define ASTEROID_BOUNDS_PADDING 100
#define ASTEROID_CONE_HALF_DEG 30
#define ASTEROID_ROTATION_SPEED_MAX_DEG 90

typedef struct Asteroid
{
    Vector2 position;
    Vector2 velocity;
    f32 rotation;
    f32 rotation_speed;

    bool is_active;
    bool is_exploding;

    Animation2D *animation;
} Asteroid;

Asteroid asteroid_init(Animation2D *animation);
i64 asteroid_update(Asteroid *asteroid, f32 frametime);
void asteroid_draw(Asteroid asteroid) ;
void asteroid_destroy(Asteroid *asteroid);
void asteroid_deinit(Asteroid *asteroid);
