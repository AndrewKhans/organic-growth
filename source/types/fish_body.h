#pragma once

constexpr unsigned int FISH_BODY_SIZE = 60;

enum class FishPart : unsigned char {
    AIR,
    BODY,
    MOUTH,
    FIN,
};

struct FishBody {
    unsigned int entityId;
    Vector2 worldCoords; // The center of the bottom of the fish, in world-coords

    // Flattened 2D vector, 0,0 is the bottom left
    std::vector<FishPart> arr;
    unsigned int width  = FISH_BODY_SIZE;
    unsigned int height = FISH_BODY_SIZE;
};