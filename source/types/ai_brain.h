#pragma once

#include "raylib.h"



struct AiBrain {
    unsigned int entityId;

    unsigned int lastMovementTick = 0;
    unsigned int currentActionEndTick = 0;
};