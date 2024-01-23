#include "defines.h"
#include "raylib.h"
#include "rlgl.h"

Texture2D texture_default_init()
{
    u64 default_texture_id = rlGetTextureIdDefault();
    Texture2D default_texture = {
        .id = default_texture_id, .width = 1, .height = 1, .format = 1, .mipmaps = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8};
    return default_texture;
}
