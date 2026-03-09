#pragma once

#include "raylib.h"
#include "constants.h"
#include <vector>

enum flowerGrowthPhase {
    SEEDLING,
    LEAFY,
    FLOWER,
};

enum plantPart {
    AIR,
    SEED,
    STEM,
    LEAFBASE,
    LEAF,
    PETALBASE,
    PETAL,
};

class Flower {
    public:
        Flower(coordPair loc);

        void grow();
        void draw();

    private:
        // Plant vars
        coordPair loc; // The center of the bottom of the plant, in graphics-coords
        std::vector<std::vector<plantPart>> plantArr; // Centered around loc. 0,0 is bottom left
        unsigned int age = 0;
        flowerGrowthPhase growthPhase = SEEDLING;

        // Where the flower is currently growing from
        coordPair growthPoint;

        // Traits assigned at birth
        Color petalColor;
        Color stemColor;
        unsigned int maxHeight;
};

