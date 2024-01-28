#pragma once

#include "asteroid.h"
#include "defines.h"
#include "raylib.h"

#define PLAYER_SPEED_MAX 200
#define PLAYER_ACCELLERATION 5
#define PLAYER_DECELLERATION 2

#define PLAYER_ROTATION_SPEED 0.05f

#define PLAYER_WRAP_PADDING 16
#define PLAYER_WRAP_NUDGE_SPEED 30

typedef struct
{
    Vector2 position;
    Vector2 velocity;
    f32 rotation;

    Texture2D texture;
    Rectangle texture_source;
} Player;

Player player_init(Vector2 position);
void player_update(Player *player, f32 frametime);
void player_draw(Player *player, Asteroid *asteroids, Shader shader, i64 shader_loc_seconds, f32 *shader_seconds,
                 Texture2D default_texture);
void player_deinit(Player *player);
