#pragma once

#include "constants.h"
#include "game_data.h"
#include "types/plant_body.h"
#include "raylib.h"


unsigned int generatePlant(Vector2 worldCoords, PlantType pt, GameData &gd);
void growPlants(GameData &gd);