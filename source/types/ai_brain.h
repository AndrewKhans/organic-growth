#pragma once

#include "raylib.h"

enum class AiTask : unsigned char {
    IDLE,
    MOVE,
    ATTACK,
    FOLLOW,
};

struct AiBrain {
    unsigned int entityId;

    AiTask task;
    unsigned int lastMovementTick = 0;
    unsigned int taskTimeout = 0;
};