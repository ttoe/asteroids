#include "asteroid.h"
#include "animation.h"
#include "constants.h"
#include "defines.h"
#include "raylib.h"
#include "raymath.h"

Asteroid asteroid_init(Animation2D *animation)
{
    i64 direction = GetRandomValue(1, 4);
    i64 location = GetRandomValue(0, WIN_SIDE);

    Vector2 position = {0};
    switch (direction)
    {
    case 1:
        // left
        position.x = -ASTEROID_SPAWN_PADDING;
        position.y = location;
        break;
    case 2:
        // right
        position.x = WIN_SIDE + ASTEROID_SPAWN_PADDING;
        position.y = location;
        break;
    case 3:
        // top
        position.x = location;
        position.y = -ASTEROID_SPAWN_PADDING;
        break;
    case 4:
        // bottom
        position.x = location;
        position.y = WIN_SIDE + ASTEROID_SPAWN_PADDING;
        break;
    }

    Vector2 velocity = Vector2Scale(Vector2Normalize(Vector2Subtract(WIN_CENTER, position)), 50);

    f32 random_angle = (f32)GetRandomValue(-ASTEROID_CONE_HALF_DEG, ASTEROID_CONE_HALF_DEG) * DEG2RAD;
    velocity = Vector2Rotate(velocity, random_angle);

    f32 random_initial_rotation = (f32)GetRandomValue(0, 359) * DEG2RAD;

    // no conversion to radians because drawing function uses degrees
    f32 random_rotation_speed = (f32)GetRandomValue(-ASTEROID_ROTATION_SPEED_MAX_DEG, ASTEROID_ROTATION_SPEED_MAX_DEG);

    return (Asteroid){.position = position,
                      .velocity = velocity,
                      .rotation = random_initial_rotation,
                      .rotation_speed = random_rotation_speed,
                      .is_active = true,
                      .is_exploding = false,
                      .animation = animation};
}

i64 asteroid_update(Asteroid *asteroid, f32 frametime)
{
    if (!asteroid->is_active)
    {
        return 0;
    }

    asteroid->position = Vector2Add(asteroid->position, Vector2Scale(asteroid->velocity, frametime));

    Rectangle outer_bounds = {.x = -ASTEROID_BOUNDS_PADDING,
                              .y = -ASTEROID_BOUNDS_PADDING,
                              .width = WIN_SIDE + 2 * ASTEROID_BOUNDS_PADDING,
                              .height = WIN_SIDE + 2 * ASTEROID_BOUNDS_PADDING};

    // deactivate if new position is out of bounds
    if (!CheckCollisionPointRec(asteroid->position, outer_bounds))
    {
        asteroid->is_active = false;
        return 0;
    }

    // if still in bounds rotate
    asteroid->rotation += asteroid->rotation_speed * frametime;

    return 1;
}

void asteroid_draw(Asteroid asteroid)
{
    if (asteroid.is_active)
    {
        animation2d_draw_frame(asteroid.animation, 0, asteroid.rotation, asteroid.position);
    }
}
