#pragma once

#include <unordered_map>
#include <vector>
#include "types/plant_body.h"
#include "types/fish_body.h"
#include "types/sprite.h"
#include "types/player_controller.h"
#include "types/physics_body.h"
#include "types/transform2.h"
#include "types/ai_brain.h"

struct GameData {
    unsigned int currentTick = 0;
    unsigned int nextEntityId = 0;

    // std::vector<Transform2> transforms;
    std::vector<Sprite> sprites;
    std::vector<FishBody> fishBodies;
    std::vector<PlantBody> plantBodies;
    std::vector<PlayerController> playerControllers;
    std::vector<PhysicsBody> physicsBodies;
    std::vector<AiBrain> aiBrains;

    // Consider replacing hashmaps with sparse arrays for performance
    std::unordered_map<unsigned int, Transform2> idToTransform2;
    std::unordered_map<unsigned int, unsigned int> idToSpriteIdx;
    std::unordered_map<unsigned int, unsigned int> idToFishBodyIdx;
    std::unordered_map<unsigned int, unsigned int> idToPlantBodyIdx;
    std::unordered_map<unsigned int, unsigned int> idToPlayerControllerIdx;
    std::unordered_map<unsigned int, unsigned int> idToPhysicsBodyIdx;
    std::unordered_map<unsigned int, unsigned int> idToAiBrainIdx;
};