#pragma once

#include "fish.h"
#include "constants.h"
#include "raylib.h"


Fish generateFish(Vector2 worldCoords);

void drawFish(std::vector<Fish> &fish);