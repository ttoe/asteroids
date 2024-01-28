#include "asteroid.h"
#include "asteroids.h"
#include "constants.h"
#include "defines.h"
#include "player.h"
#include "projectiles.h"
#include "raylib.h"
#include "raymath.h"
#include "texture_default.h"
#include "time.h"

int main(void)
{
    InitWindow(WIN_SIDE, WIN_SIDE, "Asteroids");
    SetTargetFPS(TARGET_FPS);

    Texture2D asteroid_texture = LoadTexture("assets/asteroid_explode.png");
    Animation2D asteroid_animation = animation2d_create(asteroid_texture, 96.0, 96.0, 8);

    Texture2D default_texture = texture_default_init();
    Shader shader = LoadShader(0, "shaders/damage_vignette.fs");
    i64 shader_loc_seconds = GetShaderLocation(shader, "seconds");
    f32 shader_seconds = SHADER_SECONDS;

    Player player = player_init(WIN_CENTER);

    SetRandomSeed(time(0));

    while (!WindowShouldClose())
    {
        const f32 frametime = GetFrameTime();

        player_update(&player, frametime);
        asteroids_update(&asteroid_animation, frametime);
        projectiles_update(frametime);
        projectiles_collide(asteroids_get());

        // Draw the current game state
        BeginDrawing();
        ClearBackground(BLACK);

        player_draw(&player, asteroids_get(), shader, shader_loc_seconds, &shader_seconds, default_texture);
        asteroids_draw();
        projectiles_draw();

        EndDrawing();
    }

    UnloadShader(shader);
    UnloadTexture(default_texture);
    player_deinit(&player);
    CloseWindow();

    return 0;
}
