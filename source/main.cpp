#include <chrono>
#include <thread>
#include <iostream>

#include "raylib.h"
#include "systems/plant_system.h"
#include "systems/fish_system.h"
#include "systems/render_system.h"
#include "systems/player_control_system.h"
#include "asset_loader.h"
#include "constants.h"
#include "game_data.h"

constexpr unsigned char NUM_PLANTS = 3;
constexpr double TICK_INTERVAL = 0.1; // seconds between each tick

void gameStateInit(GameData &gd) {
    int plantSpacing = WINDOW_WIDTH/(NUM_PLANTS+1);
    float xLocation = plantSpacing;
    for (int i = 0; i < NUM_PLANTS; i++) {
        generatePlant({xLocation, WINDOW_HEIGHT - 100}, PlantType::FLOWER, gd);
        xLocation += plantSpacing;
    }

    unsigned int playerFishId = generateFish(gd, {WINDOW_WIDTH/2, WINDOW_HEIGHT - 100});
    loadFishAssets(gd, playerFishId, "Fish1");
    addPlayerControllerToEntity(gd, playerFishId);
}

void gameStateUpdates(GameData &gd) {
    growPlants(gd);
}

int main(void)
{
    GameData gd;

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "organic-growth");
    SetTargetFPS(60);

    gameStateInit(gd);

    double lastTick = 0.0;

    while (!WindowShouldClose()) {
        double now = GetTime();
        if (now - lastTick >= TICK_INTERVAL) {
            gameStateUpdates(gd);
            lastTick = now;
        }
        handlePlayerInput(gd);
        drawWorld(gd.sprites);
    }

    CloseWindow();
    return 0;
}