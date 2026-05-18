#pragma once

#include "raylib.h"

struct PlayerController {
    unsigned int entityId;
    unsigned int leftKey  = KEY_LEFT;
    unsigned int rightKey = KEY_RIGHT;
    unsigned int upKey    = KEY_UP;
    unsigned int downKey  = KEY_DOWN;
};