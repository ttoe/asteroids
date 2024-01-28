#include "animation.h"
#include "assert.h"
#include "defines.h"
#include "raylib.h"

Animation2D animation2d_create(Texture2D texture, f32 frame_width, f32 frame_height, u64 number_of_frames)
{
    return (Animation2D){
        .texture = texture,
        .frame_source = (Rectangle){.x = 0, .y = 0, .width = frame_width, .height = frame_height},
        .number_of_frames = number_of_frames,
    };
}

void animation2d_draw_frame(Animation2D *animation, u64 framenumber, f32 rotation, Vector2 dest)
{
    // TODO: make pro version

    const i64 fs_width = animation->frame_source.width;
    const i64 fs_height = animation->frame_source.height;

    // center by default and source equals destination
    Vector2 origin = {fs_width / 2.0, fs_height / 2.0};
    Rectangle src_rect = {.x = fs_width * framenumber, .y = 0, .width = fs_width, .height = fs_height};
    Rectangle dest_rect = {.x = dest.x, .y = dest.y, fs_width, fs_height};

    DrawTexturePro(animation->texture, src_rect, dest_rect, origin, rotation, WHITE);
}
