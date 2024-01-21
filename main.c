#include "constants.h"
#include "defines.h"
#include "player.h"
#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"

f32 win_width = 700;
f32 win_height = 700;

int main(void)
{
    InitWindow(win_width, win_height, "Asteroids");
    // SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(TARGET_FPS);

    Shader shader = LoadShader(NULL, "shaders/damage_vignette.fs");

    i64 shader_loc_seconds = GetShaderLocation(shader, "seconds");

    const Texture2D ship = LoadTexture("assets/ship.png");
    const Rectangle ship_source = {0, 0, 48, 48};

    Player p = {.position = ORIGIN, .rotation = 0, .speed = 0};

    u64 default_texture_id = rlGetTextureIdDefault();
    Texture2D default_texture = {
        .id = default_texture_id, .width = 1, .height = 1, .format = 1, .mipmaps = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8};

    f32 shader_seconds = 1.2;

    while (!WindowShouldClose())
    {
        // Update game state before drawing
        const f32 frametime = GetFrameTime();

        player_velocity_update(&p);
        player_position_update(&p, frametime);

        // Draw the current game state
        BeginDrawing();
        ClearBackground(BLACK);

        Rectangle ship_dest = {p.position.x, p.position.y, 48, 48};
        DrawTexturePro(ship, ship_source, ship_dest, (Vector2){24, 24}, p.rotation * RAD2DEG, WHITE);

        // DEBUG
        // draw player velocity
        DrawCircleV(Vector2Add(p.position, Vector2Scale(Vector2Rotate(VEC_R, p.rotation), p.speed)), 5, WHITE);

        if (IsKeyPressed(KEY_SPACE))
        {
            shader_seconds = 1.2;
        }

        if (shader_seconds > 0)
        {
            Rectangle source = {.x = 0, .y = 0, .width = 1, .height = 1};
            Rectangle dest = {.x = 0, .y = 0, .width = win_width, .height = win_height};

            SetShaderValue(shader, shader_loc_seconds, &shader_seconds, SHADER_UNIFORM_FLOAT);

            BeginShaderMode(shader);
            DrawTexturePro(default_texture, source, dest, (Vector2){0, 0}, 0, WHITE);
            EndShaderMode();

            shader_seconds -= GetFrameTime();
        }

        DrawFPS(0, 0);
        EndDrawing();
    }

    UnloadShader(shader);
    UnloadTexture(default_texture);
    UnloadTexture(ship);
    CloseWindow();

    return 0;
}
