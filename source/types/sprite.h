#pragma once

#include "raylib.h"
#include <vector>

constexpr unsigned int SPRITE_SIZE = 32;

struct Sprite {
    unsigned int entityId;

    Vector2 worldCoords; // The center of the sprite
    float rotation = 0;

    // Flattened 2D vector, 0,0 is the bottom left
    // TODO: Consider pulling width/height out of the sprite if all of them
    //       remain the same size
    std::vector<Color> pixels;
    unsigned int width  = SPRITE_SIZE;
    unsigned int height = SPRITE_SIZE;
};
