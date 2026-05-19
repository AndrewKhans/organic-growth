#pragma once

#include "raylib.h"

struct PhysicsBody {
    unsigned int entityId;

    float mass;
    Vector2 velocity;
    // float velocity;
    // float direction; // Based on unit circle, Directly right is 0, down is 90
};
