#pragma once

#include "defines.h"
#include "raylib.h"

typedef struct
{
    Vector2 position;
    f32 rotation;
    f32 speed;
} Player;

Player player_init(Vector2 position, f32 rotation, f32 speed);
void player_velocity_update(Player *player);
void player_position_update(Player *player, f32 frametime);
