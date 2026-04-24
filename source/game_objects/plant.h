/*
    Aim to keep the Plant struct small, so that growPlants in plant_system stays efficient
*/

#include "constants.h"
#include "raylib.h"

constexpr unsigned int PLANT_ARR_WIDTH = 60;
constexpr unsigned int PLANT_ARR_HEIGHT = 60;

enum class PlantType : unsigned int {
    FLOWER,
    TREE,
};

enum class PlantPart : unsigned int {
    AIR,
    SEED,
    STEM,
    LEAFBASE,
    LEAF,
    PETALBASE,
    PETAL,
};

enum class GrowthPhase : unsigned int {
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
    std::array<PlantPart, PLANT_ARR_WIDTH*PLANT_ARR_HEIGHT> plantArr;
    std::array<Color, PLANT_ARR_WIDTH*PLANT_ARR_HEIGHT> sprite;

    Color petalColor;
    Color stemColor;
    Color barkColor;
} Plant;
