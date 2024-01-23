#include "player.h"
#include "animation.h"
#include "constants.h"
#include "defines.h"
#include "projectiles.h"
#include "raylib.h"
#include "raymath.h"

Player player_init(Vector2 position)
{
    // TODO: asset loading system
    const Texture2D texture = LoadTexture("assets/ship.png");
    const Rectangle texture_source = {0, 0, 32, 32};

    return (Player){
        .position = position, .velocity = VEC_R, .rotation = 0, .texture = texture, .texture_source = texture_source};
}

void player_velocity_update(Player *player)
{
    if (IsKeyDown(KEY_LEFT))
    {
        player->rotation -= PLAYER_ROTATION_SPEED;
    }
    if (IsKeyDown(KEY_RIGHT))
    {
        player->rotation += PLAYER_ROTATION_SPEED;
    }

    Vector2 facing_direction = Vector2Rotate(VEC_R, player->rotation);

    if (IsKeyDown(KEY_DOWN))
    {
        player->velocity = Vector2Subtract(player->velocity, Vector2Scale(facing_direction, PLAYER_DECELLERATION));
    }
    if (IsKeyDown(KEY_UP))
    {
        player->velocity = Vector2Add(player->velocity, Vector2Scale(facing_direction, PLAYER_ACCELLERATION));
    }
}

void player_position_wrap(Player *player)
{
    // TODO nudge player velocity
    if (player->position.x < 0 - PLAYER_WRAP_PADDING)
    {
        // teleport to right window edge
        player->position.x = WIN_SIDE;
    } else if (player->position.x > WIN_SIDE + PLAYER_WRAP_PADDING)
    {
        // teleport to left window edge
        player->position.x = 0;
    }

    if (player->position.y < 0 - PLAYER_WRAP_PADDING)
    {
        // teleport to bottom window edge
        player->position.y = WIN_SIDE;
    } else if (player->position.y > WIN_SIDE + PLAYER_WRAP_PADDING)
    {
        // teleport to top window edge
        player->position.y = 0;
    }
}

void player_position_update(Player *player, f32 frametime)
{
    player->position = Vector2Add(player->position, Vector2Scale(player->velocity, frametime));
    player_position_wrap(player);
}

void player_projectile_shoot(Player *player, f32 frametime)
{
    Animation2D a = {0};
    if (IsKeyDown(KEY_LEFT_SHIFT))
    {
        projectiles_create(&a, player, frametime);
    }
}

void player_update(Player *player, f32 frametime)
{
    player_velocity_update(player);
    player_position_update(player, frametime);
    player_projectile_shoot(player, frametime);
}

void player_draw(Player *player)
{
    Rectangle texture_dest = {player->position.x, player->position.y, 32, 32};
    Vector2 origin = {16, 16};
    DrawTexturePro(player->texture, player->texture_source, texture_dest, origin, player->rotation * RAD2DEG, WHITE);
}

void player_deinit(Player *player)
{
    // called when the game ends to free textures
    UnloadTexture(player->texture);
}
