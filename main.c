#include "asteroid.h"
#include "asteroids.h"
#include "constants.h"
#include "defines.h"
#include "player.h"
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

    f32 shader_seconds = 1.2;

    Player player = player_init(WIN_CENTER, 0.0, 0.0);

    SetRandomSeed(time(0));

    while (!WindowShouldClose())
    {
        const f32 frametime = GetFrameTime();

        player_update(&player, frametime);
        asteroids_create(&asteroid_animation, frametime);
        i64 active_asteroids = asteroids_update(frametime);

        // Draw the current game state
        BeginDrawing();
        ClearBackground(BLACK);

        player_draw(&player);
        asteroids_draw();

        if (IsKeyPressed(KEY_SPACE))
        {
            shader_seconds = 1.2;
        }

        if (shader_seconds > 0)
        {
            Rectangle source = {.x = 0, .y = 0, .width = 1, .height = 1};
            Rectangle dest = {.x = 0, .y = 0, .width = WIN_SIDE, .height = WIN_SIDE};

            SetShaderValue(shader, shader_loc_seconds, &shader_seconds, SHADER_UNIFORM_FLOAT);

            BeginShaderMode(shader);
            DrawTexturePro(default_texture, source, dest, (Vector2){0, 0}, 0, WHITE);
            EndShaderMode();

            shader_seconds -= GetFrameTime();
        }

        // TODO: move all debug function into own file and call here

        // draw player velocity
        DrawCircleV(Vector2Add(player.position, Vector2Scale(Vector2Rotate(VEC_R, player.rotation), player.speed)), 5,
                    WHITE);
        DrawFPS(0, 0);
        DrawText(TextFormat("active asteroids %d", active_asteroids), 0, 20, 20, RED);

        EndDrawing();
    }

    UnloadShader(shader);
    UnloadTexture(default_texture);
    player_deinit(&player);
    CloseWindow();

    return 0;
}
