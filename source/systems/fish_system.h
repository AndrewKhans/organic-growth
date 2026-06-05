#pragma once

#include "raylib.h"
#include "game_data.h"
#include "types/fish_body.h"
#include "types/sprite.h"
#include "systems/physics_system.h"
#include "asset_loader.h"


unsigned int addFish(GameData &gd, Transform2 t);
void handleFishCollisions(GameData &gd);
