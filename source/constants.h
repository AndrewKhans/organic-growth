#pragma once

#include "raylib.h"
#include "types/transform2.h"
#include <random>

constexpr unsigned int WINDOW_WIDTH = 1280;
constexpr unsigned int WINDOW_HEIGHT = 720;

constexpr unsigned int PIXEL_SIZE = 12;

// constexpr unsigned int SCREEN_WIDTH = 900;
// constexpr unsigned int SCREEN_HEIGHT = 700;

#define IS_BLANK(c) ((c).r == 0 && (c).g == 0 && (c).b == 0 && (c).a == 0)

struct uIntPair {
    unsigned int x = 0;
    unsigned int y = 0;
};

static inline float dist2d(Vector2 v1, Vector2 v2) {
    return sqrtf((v1.x - v2.x)*(v1.x - v2.x) + (v1.y - v2.y)*(v1.y - v2.y));
}

static inline Vector2 localToWorldCoords(const Vector2 &localCoords, const Vector2 &size, const Transform2 &t) {
    Vector2 offset = {(size.x/2)*PIXEL_SIZE - PIXEL_SIZE/2, (size.y/2)*PIXEL_SIZE - PIXEL_SIZE/2};
    float rot = t.rot - 180.0f;
    float rads = rot * (PI / 180);
    float xCoord = localCoords.x*PIXEL_SIZE - offset.x;
    float yCoord = localCoords.y*PIXEL_SIZE - offset.y + 10;

    Vector2 worldCoords;
    worldCoords.x = t.x + (xCoord*cosf(rads) - yCoord*sinf(rads));
    worldCoords.y = t.y + (xCoord*sinf(rads) + yCoord*cosf(rads));

    return worldCoords;
}

static inline int randInt(int min, int max) {
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(rng);
}