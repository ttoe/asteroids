#include "player.h"
#include "constants.h"
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

void player_position_update(Player *player, f32 frametime)
{
    const Vector2 vector_to_add = Vector2Scale(Vector2Rotate(VEC_R, player->rotation), player->speed * frametime);
    player->position = Vector2Add(player->position, vector_to_add);
}
