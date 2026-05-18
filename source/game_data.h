#pragma once

#include <unordered_map>
#include <vector>
#include "types/plant_body.h"
#include "types/fish_body.h"
#include "types/sprite.h"
#include "types/player_controller.h"

struct GameData {
    unsigned int nextEntityId = 0;

    std::vector<Sprite> sprites;
    std::vector<FishBody> fishBodies;
    std::vector<PlantBody> plantBodies;
    std::vector<PlayerController> playerControllers;

    // consider replacing hashmaps with sparse arrays for performance
    std::unordered_map<unsigned int, unsigned int> idToSpriteIdx;
    std::unordered_map<unsigned int, unsigned int> idToFishBodyIdx;
    std::unordered_map<unsigned int, unsigned int> idToPlantBodyIdx;
    std::unordered_map<unsigned int, unsigned int> idToPlayerControllerIdx;
};