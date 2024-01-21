#include "player.h"
#include "constants.h"
#include "defines.h"
#include "raylib.h"
#include "raymath.h"

Player player_init(Vector2 position, f32 rotation, f32 speed)
{
    return (Player){.position = position, .rotation = rotation, .speed = speed};
}

void player_velocity_update(Player *player)
{
    if (IsKeyDown(KEY_LEFT))
    {
        player->rotation -= 0.05f;
    }
    if (IsKeyDown(KEY_RIGHT))
    {
        player->rotation += 0.05f;
    }
    if (IsKeyDown(KEY_DOWN))
    {
        player->speed -= 3;
    }
    if (IsKeyDown(KEY_UP))
    {
        player->speed += 3;
    }
}

void player_position_wrap(Player *player)
{
    if (player->position.x < 0 - PLAYER_WRAP_PADDING)
    {
        // teleport to right window edge
        player->position.x = WIN_WIDTH;
        // nudge player speed
        player->speed = MAX(player->speed, PLAYER_WRAP_NUDGE_SPEED);
    } else if (player->position.x > WIN_WIDTH + PLAYER_WRAP_PADDING)
    {
        // teleport to left window edge
        player->position.x = 0;
        // nudge player speed
        player->speed = MAX(player->speed, PLAYER_WRAP_NUDGE_SPEED);
    }

    if (player->position.y < 0 - PLAYER_WRAP_PADDING)
    {
        // teleport to bottom window edge
        player->position.y = WIN_WIDTH;
        // nudge player speed
        player->speed = MAX(player->speed, PLAYER_WRAP_NUDGE_SPEED);
    } else if (player->position.y > WIN_HEIGHT + PLAYER_WRAP_PADDING)
    {
        // teleport to top window edge
        player->position.y = 0;
        // nudge player speed
        player->speed = MAX(player->speed, PLAYER_WRAP_NUDGE_SPEED);
    }
}

void player_position_update(Player *player, f32 frametime)
{
    const Vector2 vector_to_add = Vector2Scale(Vector2Rotate(VEC_R, player->rotation), player->speed * frametime);
    player->position = Vector2Add(player->position, vector_to_add);

    player_position_wrap(player);
}

void player_update(Player *player, f32 frametime)
{
    player_velocity_update(player);
    player_position_update(player, frametime);
}
