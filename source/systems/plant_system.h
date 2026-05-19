#pragma once

#include "constants.h"
#include "game_data.h"
#include "types/plant_body.h"
#include "raylib.h"

unsigned int addFlower(GameData &gd, Vector2 worldCoords);

void growPlants(GameData &gd);