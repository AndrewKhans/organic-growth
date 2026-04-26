#include "constants.h"
#include "raylib.h"
#include <cstdint>
#include <vector>

constexpr unsigned int FISH_ARR_SIZE = 60;

enum class BodyFunction : unsigned char {
    AIR,
    BODY,
    MOUTH,
    FIN,
};

struct FishPart {
    BodyFunction bf;
    Color c;
}

typedef struct Fish {
    Vector2 worldCoords; // The center of the bottom of the fish, in world-coords

    // Flattened 2D vector, 0,0 is the bottom left
    std::vector<FishPart> bodyArr;
    std::vector<Color> sprite;
    unsigned int arrWidth = FISH_ARR_SIZE;
    unsigned int arrHeight = FISH_ARR_SIZE;
};
