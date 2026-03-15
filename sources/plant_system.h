#pragma once

#include "constants.h"
#include "raylib.h"
#include <vector>

enum class PlantType : uint8_t {
    FLOWER,
    TREE,
};

enum class PlantPart : uint8_t {
    AIR,
    SEED,
    STEM,
    LEAFBASE,
    LEAF,
    PETALBASE,
    PETAL,
};

enum class GrowthPhase : uint8_t {
    SEED,
    SPROUT,
    BARKY,
    FLOWERING,
    DORMANT,
};


typedef struct Plant {
    PlantType type;
    CoordPair loc;         // The center of the bottom of the plant, in graphics-coords
    CoordPair growthPoint; // Where the plant is currently growing from


    GrowthPhase growthPhase = GrowthPhase::SEED;
    unsigned int growthPoints = 0;

    // Flattened 2D vector, 0,0 is the bottom left
    std::vector<PlantPart> plantArr;
    unsigned int arrWidth = 60;
    unsigned int arrHeight = 60;

    Color petalColor;
    Color stemColor;
    Color barkColor;
} Plant;

Plant generateFlower(CoordPair seedLocation);
void growPlants(std::vector<Plant> &plants);
void drawPlants(std::vector<Plant> &plants);