#pragma once

#include <random>

constexpr unsigned int WINDOW_WIDTH = 900;
constexpr unsigned int WINDOW_HEIGHT = 700;

constexpr unsigned int SCREEN_WIDTH = 900;
constexpr unsigned int SCREEN_HEIGHT = 700;


// Game constants

struct uIntPair {
    unsigned int x = 0;
    unsigned int y = 0;
};

static inline int randInt(int min, int max) {
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(rng);
}