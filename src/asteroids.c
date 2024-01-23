#include "asteroids.h"
#include "animation.h"
#include "asteroid.h"
#include "defines.h"
#include "raylib.h"
#include "raymath.h"

static Asteroid _asteroids[ASTEROIDS_MAX] = {0};
static f32 _last_asteroid_spawn_time = ASTEROIDS_SPAWN_DELAY;

void asteroids_create(Animation2D *animation, f32 frametime)
{
    _last_asteroid_spawn_time += frametime;
    if (_last_asteroid_spawn_time < ASTEROIDS_SPAWN_DELAY)
    {
        return;
    }

    for (usize i = 0; i < ASTEROIDS_MAX; i++)
    {
        if (!_asteroids[i].is_active)
        {
            _asteroids[i] = asteroid_init(animation);
            _last_asteroid_spawn_time = 0;
            return;
        }
    }
}

i64 asteroids_update(f32 frametime)
{
    i64 active_asteroids = 0;
    for (usize i = 0; i < ASTEROIDS_MAX; i++)
    {
        active_asteroids += asteroid_update(&_asteroids[i], frametime);
    }

    return active_asteroids;
}

void asteroids_draw()
{
    for (usize i = 0; i < ASTEROIDS_MAX; i++)
    {
        asteroid_draw(_asteroids[i]);
    }
}
