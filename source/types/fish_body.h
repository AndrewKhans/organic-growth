#pragma once

constexpr unsigned int FISH_BODY_SIZE = 32;

enum class FishPart : unsigned char {
    AIR,
    BODY,
    MOUTH,
    FIN,
};

struct FishBody {
    unsigned int entityId;

    // Flattened 2D vector, 0,0 is the bottom left
    std::vector<FishPart> arr;
    unsigned int width  = FISH_BODY_SIZE;
    unsigned int height = FISH_BODY_SIZE;

    // Cached values
    float swimForce;
    Vector2 mouthLocation;
};
