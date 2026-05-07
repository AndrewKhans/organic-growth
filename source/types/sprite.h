#pragma once

#include "raylib.h"
#include <vector>

struct Sprite {
    unsigned int entityId;
    Vector2 worldCoords; // The center of the bottom of the sprite
    std::vector<Color> pixels;
    unsigned int width, height;
};