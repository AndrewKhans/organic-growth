#pragma once

#include "raylib.h"
#include "constants.h"

constexpr unsigned int PLANT_BODY_SIZE = 60;

enum class PlantType : unsigned char {
    ALGAE,
    FLOWER
};

enum class PlantPart : unsigned char {
    AIR,
    SEED,
    STEM,
    LEAFBASE,
    LEAF,
    PETALBASE,
    PETAL,
};

enum class GrowthPhase : unsigned char {
    SEED,
    SPROUT,
    FLOWERING,
    DORMANT,
};

struct PlantBody {
    unsigned int entityId;
    Vector2 worldCoords; // The center of the bottom of the plant, in world-coords

    PlantType type;
    Color petalColor;
    Color stemColor;

    uIntPair growthLoc; // Where the plant is currently growing from in plantarr
    GrowthPhase growthPhase = GrowthPhase::SEED;
    unsigned int growthPoints = 0;

    // Flattened 2D vector, 0,0 is the bottom left
    std::vector<PlantPart> arr;
    unsigned int width  = PLANT_BODY_SIZE;
    unsigned int height = PLANT_BODY_SIZE;
};
