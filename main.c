#include "constants.h"
#include "defines.h"
#include "player.h"
#include "raylib.h"
#include "raymath.h"
#include "texture_default.h"

int main(void)
{
    InitWindow(WIN_WIDTH, WIN_HEIGHT, "Asteroids");
    SetTargetFPS(TARGET_FPS);

    Texture2D default_texture = texture_default_init();
    Shader shader = LoadShader(0, "shaders/damage_vignette.fs");
    i64 shader_loc_seconds = GetShaderLocation(shader, "seconds");
    f32 shader_seconds = 1.2;

    const Texture2D asteroid = LoadTexture("assets/asteroid_explode.png");
    const Rectangle asteroid_source = {0, 0, 96, 96};

    Player player = player_init(WIN_CENTER, 0.0, 0.0);

    while (!WindowShouldClose())
    {
        // Update game state before drawing
        const f32 frametime = GetFrameTime();

        player_update(&player, frametime);

        // Draw the current game state
        BeginDrawing();
        ClearBackground(BLACK);

        player_draw(&player);

        if (IsKeyPressed(KEY_SPACE))
        {
            shader_seconds = 1.2;
        }

        if (shader_seconds > 0)
        {
            Rectangle source = {.x = 0, .y = 0, .width = 1, .height = 1};
            Rectangle dest = {.x = 0, .y = 0, .width = WIN_WIDTH, .height = WIN_HEIGHT};

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

        EndDrawing();
    }

    UnloadShader(shader);
    UnloadTexture(default_texture);
    player_deinit(&player);
    CloseWindow();

    return 0;
}
