#pragma once

#include "raylib.h"
#include "game_data.h"
#include "types/physics_body.h"
#include <vector>

void applyAccel(GameData &gd, unsigned int entityId, Vector2 accel);
void simulatePhysics(GameData &gd);
