#include <chrono>
#include <thread>
#include <iostream>

#include "raylib.h"
#include "systems/plant_system.h"
#include "systems/fish_system.h"
#include "systems/render_system.h"
#include "systems/player_control_system.h"
#include "systems/physics_system.h"
#include "systems/ai_system.h"
#include "asset_loader.h"
#include "constants.h"
#include "game_data.h"

constexpr unsigned char NUM_PLANTS = 3;
constexpr double TICK_INTERVAL = 1/60; // seconds between each tick

void gameStateInit(GameData &gd) {
    int plantSpacing = WINDOW_WIDTH/(NUM_PLANTS+1);
    float xLocation = plantSpacing;
    // for (int i = 0; i < NUM_PLANTS; i++) {
    //     addFlower(gd, {xLocation, WINDOW_HEIGHT/3, 0});
    //     xLocation += plantSpacing;
    // }

    unsigned int playerFishId = addFish(gd, {WINDOW_WIDTH/2, WINDOW_HEIGHT/2, 0});
    addPlayerController(gd, playerFishId);

    for (int i = 0; i < 1; i++) {
        unsigned int fishId = addFish(gd, {WINDOW_WIDTH/2, WINDOW_HEIGHT/4, 0});
        addAiBrain(gd, fishId);
    }
}

void gameStateUpdates(GameData &gd) {
    growPlants(gd);
    handleFishCollisions(gd);
    aiDecisions(gd);
    simulatePhysics(gd);
}

int main(void)
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "organic-growth");
    SetTargetFPS(60);

    GameData gd;
    gameStateInit(gd);

    double lastTickTime = 0.0;
    while (!WindowShouldClose()) {
        double now = GetTime();
        if (now - lastTickTime >= TICK_INTERVAL) {
            gameStateUpdates(gd);
            handlePlayerInput(gd);
            drawWorld(gd);

            gd.currentTick++;
            lastTickTime = now;
        }
    }

    CloseWindow();
    return 0;
}