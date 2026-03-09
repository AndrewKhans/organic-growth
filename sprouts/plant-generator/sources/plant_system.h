#pragma once

#include "constants.h"
#include "raylib.h"
#include <vector>

enum PlantType {
    FLOWER,
    TREE,
};

enum PlantPart {
    AIR,
    SEED,
    STEM,
    LEAFBASE,
    LEAF,
    PETALBASE,
    PETAL,
};

enum GrowthPhase {
    SEEDLING,
    SPROUT,
    FLOWERING,
    DORMANT,
};

typedef struct Plant {
    PlantType type;
    CoordPair loc;         // The center of the bottom of the plant, in graphics-coords
    CoordPair growthPoint; // Where the plant is currently growing from
    GrowthPhase growthPhase = SEEDLING;
    unsigned int age = 0;

    std::vector<PlantPart> plantArr; // Centered around loc. 0,0 is bottom left
    unsigned int arrWidth = 60;
    unsigned int arrHeight = 60;

    Color petalColor;
    Color stemColor;
    Color barkColor;
} Plant;

Plant generateFlower(CoordPair seedLocation);
void growPlants(std::vector<Plant> &plants);
void drawPlants(std::vector<Plant> &plants);