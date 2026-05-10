#pragma once

#include <unordered_map>
#include <vector>
#include "types/plant_body.h"
#include "types/fish_body.h"
#include "types/sprite.h"

struct GameData {
    unsigned int nextEntityId = 0;

    std::vector<Sprite> sprites;
    std::vector<FishBody> fishBodies;
    std::vector<PlantBody> plantBodies;

    // idToSpriteIdx[entity id] = index of corresponding sprite in sprites
    // std::vector<unsigned int> idToSpriteIdx; // consider replacing with sparse arrays for performance
};