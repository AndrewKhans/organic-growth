#pragma once

#include "raylib.h"
#include <vector>

constexpr unsigned int SPRITE_SIZE = 60;


struct Sprite {
    unsigned int entityId;
    Vector2 worldCoords; // The center of the bottom of the sprite

    std::vector<Color> pixels;
    unsigned int width  = SPRITE_SIZE;
    unsigned int height = SPRITE_SIZE;
};