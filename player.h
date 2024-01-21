#pragma once

#include "defines.h"
#include "raylib.h"

#define PLAYER_WRAP_PADDING 16
#define PLAYER_WRAP_NUDGE_SPEED 30

typedef struct
{
    Vector2 position;
    f32 rotation;
    f32 speed;
} Player;

Player player_init(Vector2 position, f32 rotation, f32 speed);
void player_update(Player *player, f32 frametime);
