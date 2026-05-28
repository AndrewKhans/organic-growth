#pragma once

#include "raylib.h"

struct PhysicsBody {
    unsigned int entityId;

    float mass;
    Vector2 velocity; // 0, -1 is North and 1, 0 is East
};
