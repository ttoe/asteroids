#include "projectile.h"
#include "animation.h"
#include "asteroid.h"
#include "constants.h"
#include "defines.h"
#include "player.h"
#include "raylib.h"
#include "raymath.h"

Projectile projectile_init(Animation2D *animation, Player *player)
{
    Vector2 player_facing_direction = Vector2Rotate(VEC_R, player->rotation);

    Vector2 projectile_velocity = Vector2Scale(player_facing_direction, PROJECTILE_SPEED);

    return (Projectile){.position = player->position, .velocity = projectile_velocity, .is_active = true};
}

i64 projectile_update(Projectile *projectile, f32 frametime)
{
    i64 is_projectile_active = 0;

    if (projectile->is_active)
    {
        projectile->position = Vector2Add(projectile->position, Vector2Scale(projectile->velocity, frametime));
        is_projectile_active = 1;
    }

    // TODO move padding for asteroids and projectiles into constants
    Rectangle outer_bounds = {.x = -ASTEROID_BOUNDS_PADDING,
                              .y = -ASTEROID_BOUNDS_PADDING,
                              .width = WIN_SIDE + 2 * ASTEROID_BOUNDS_PADDING,
                              .height = WIN_SIDE + 2 * ASTEROID_BOUNDS_PADDING};

    // deactivate if new position is out of bounds
    if (!CheckCollisionPointRec(projectile->position, outer_bounds))
    {
        projectile->is_active = false;
        is_projectile_active = 0;
    }

    return is_projectile_active;
}

void projectile_draw(Projectile projectile)
{
    if (projectile.is_active)
    {
        f32 projectile_rotation = Vector2Angle(VEC_R, projectile.velocity) * RAD2DEG;
        Rectangle r = {.x = projectile.position.x, .y = projectile.position.y, .width = 20, .height = 2};
        DrawRectanglePro(r, (Vector2){r.width / 2.0, r.height / 2.0}, projectile_rotation, RED);
    }
}

void projectile_collide(Projectile *projectile, Asteroid *asteroid)
{
    if (!(projectile->is_active && asteroid->is_active))
    {
        return;
    }

    // TODO: do not use hardcoded projectile length/2
    // Also possible: increase radius of hit circle -- no projectile front calculation needed
    Vector2 projectile_front =
        Vector2Add(projectile->position, Vector2Scale(Vector2Normalize(projectile->velocity), 10));
    if (CheckCollisionPointCircle(projectile_front, asteroid->position, ASTEROID_COLLISION_RADIUS))
    {
        projectile->is_active = false;
        asteroid->is_active = false;
        asteroid->is_exploding = true;
    }
}
