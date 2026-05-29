#pragma once

#include "raylib.h"
#include "types/ai_brain.h"
#include "game_data.h"
#include "constants.h"
#include "physics_system.h"

void addAiBrain(GameData& gd, unsigned int entityId);
void aiDecisions(GameData &gd, unsigned int tickCount);
