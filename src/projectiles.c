#include "projectiles.h"
#include "animation.h"
#include "projectile.h"
#include "raylib.h"

static Projectile _projectiles[PROJECTILES_MAX] = {0};
static f32 _last_projectile_shoot_time = 0;

void projectiles_create(Animation2D *animation, Player *player, f32 frametime)
{
    _last_projectile_shoot_time += frametime;
    if (_last_projectile_shoot_time < PROJECTILE_RELOAD_TIME)
    {
        return;
    }

    for (usize i = 0; i < PROJECTILES_MAX; i++)
    {
        if (!_projectiles[i].is_active)
        {
            _projectiles[i] = projectile_init(animation, player);
            _last_projectile_shoot_time = 0;
            return;
        }
    }
}

i64 projectiles_update(f32 frametime)
{
    i64 active_projectiles = 0;
    for (usize i = 0; i < PROJECTILES_MAX; i++)
    {
        active_projectiles += projectile_update(&_projectiles[i], frametime);
    }

    return active_projectiles;
}

void projectiles_draw()
{
    for (usize i = 0; i < PROJECTILES_MAX; i++)
    {
        projectile_draw(_projectiles[i]);
    }
}
