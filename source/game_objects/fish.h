#include "constants.h"
#include "raylib.h"
#include <cstdint>
#include <vector>

constexpr unsigned int FISH_ARR_SIZE = 60;

enum class FishPart : unsigned char {
    AIR,
    BODY,
    MOUTH,
    FIN,
};

typedef struct Fish {
    Vector2 worldCoords; // The center of the bottom of the fish, in world-coords

    // Flattened 2D vector, 0,0 is the bottom left
    std::array<FishPart> bodyArr;
    std::array<Color> sprite;
    unsigned int arrWidth = FISH_ARR_SIZE;
    unsigned int arrHeight = FISH_ARR_SIZE;
} Fish;
