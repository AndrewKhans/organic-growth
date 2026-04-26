/*
    Aim to keep the Plant struct small, so that growPlants in plant_system stays efficient
*/

#include "constants.h"
#include "raylib.h"
#include <vector>

constexpr unsigned int PLANT_ARR_WIDTH = 60;
constexpr unsigned int PLANT_ARR_HEIGHT = 60;

enum class PlantType : unsigned char {
    FLOWER,
    TREE,
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
    BARKY,
    FLOWERING,
    DORMANT,
};

typedef struct Plant {
    PlantType type;
    Vector2 worldCoords; // The center of the bottom of the plant, in world-coords
    CoordPair growthLoc; // Where the plant is currently growing from in plantarr

    GrowthPhase growthPhase = GrowthPhase::SEED;
    unsigned int growthPoints = 0;

    // Flattened 2D vector, 0,0 is the bottom left
    std::vector<PlantPart> plantArr;
    std::vector<Color> sprite;

    Color petalColor;
    Color stemColor;
    Color barkColor;
};
