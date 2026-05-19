#pragma once

#include "raylib.h"
#include "game_data.h"
#include "types/physics_body.h"
#include <vector>
#include <iostream>

void applyForce(GameData &gd, unsigned int entityId, Vector2 force);
void simulatePhysics(GameData &gd);
