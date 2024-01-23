#pragma once

#include "defines.h"
#include "raylib.h"

typedef struct Animation2D
{
    Texture2D texture;
    Rectangle frame_source;
    u64 number_of_frames;
} Animation2D;

Animation2D animation2d_create(Texture2D texture, f32 frame_width, f32 frame_height, u64 number_of_frames);
void animation2d_draw_frame_pro(Animation2D *animation, u64 framenumber, Rectangle dest, Vector2 origin, f32 rotation,
                                Color tint);
void animation2d_draw_frame(Animation2D *animation, u64 framenumber, f32 rotation, Vector2 dest);
