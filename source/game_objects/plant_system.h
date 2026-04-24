#pragma once

#include "plant.h"
#include "constants.h"
#include "raylib.h"


Plant generatePlant(Vector2 worldCoords, PlantType pt);

void growPlants(std::vector<Plant> &plants);
void drawPlants(std::vector<Plant> &plants);