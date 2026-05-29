#pragma once

#include "raylib.h"
#include "game_data.h"
#include "types/physics_body.h"
#include <vector>
#include <iostream>

void applyForce(PhysicsBody& pb, Vector2 force);
void simulatePhysics(GameData &gd);
