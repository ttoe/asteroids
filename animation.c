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

void animation2d_draw_frame_pro(Animation2D *animation, u64 framenumber, Rectangle dest, Vector2 origin, f32 rotation,
                                Color tint)
{
    assert(framenumber <= animation->number_of_frames);
    DrawTexturePro(animation->texture, animation->frame_source, dest, origin, rotation, tint);
}

void animation2d_draw_frame(Animation2D *animation, u64 framenumber, f32 rotation, Vector2 dest)
{
    assert(framenumber <= animation->number_of_frames);

    // center by default and source equals destination
    Vector2 origin = {animation->frame_source.width / 2.0, animation->frame_source.height / 2.0};
    Rectangle dest_rect = {.x = dest.x, .y = dest.y, animation->frame_source.width, animation->frame_source.height};

    DrawTexturePro(animation->texture, animation->frame_source, dest_rect, origin, rotation, WHITE);
}
