#include <chrono>
#include <thread>
#include <iostream>

#include "raylib.h"
#include "systems/plant_system.h"
#include "systems/fish_system.h"
#include "systems/render_system.h"
#include "constants.h"
#include "game_data.h"

constexpr unsigned char NUM_PLANTS = 1;

void gameStateInit(GameData &gd) {
    int plantSpacing = WINDOW_WIDTH/(NUM_PLANTS+1);
    float xLocation = plantSpacing;
    for (int i = 0; i < NUM_PLANTS; i++) {
        generatePlant({xLocation, WINDOW_HEIGHT - 100}, PlantType::FLOWER, gd);
        xLocation += plantSpacing;
    }
}

void gameStateUpdates(GameData &gd) {
    growPlants(gd);
}

// void handleUserInput() {
//     if (IsKeyDown(KEY_RIGHT)) playerFish.worldCoords.x += 2.0f;
//     if (IsKeyDown(KEY_LEFT))  playerFish.worldCoords.x -= 2.0f;
//     if (IsKeyDown(KEY_UP))    playerFish.worldCoords.y -= 2.0f;
//     if (IsKeyDown(KEY_DOWN))  playerFish.worldCoords.y += 2.0f;
// }

int main(void)
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "organic-growth");
    SetTargetFPS(60);

    GameData gd;
    gameStateInit(gd);

    double lastTick = 0.0;
    const double tickInterval = 0.1; // seconds between each tick

    while (!WindowShouldClose()) {
        double now = GetTime();
        if (now - lastTick >= tickInterval) {
            gameStateUpdates(gd);
            lastTick = now;
        }
        // handleUserInput();
        drawWorld(gd.sprites);
    }

    CloseWindow();
    return 0;
}