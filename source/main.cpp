#include <chrono>
#include <thread>
#include <iostream>

#include "raylib.h"
#include "systems/plant_system.h"
#include "systems/fish_system.h"
#include "systems/render_system.h"
#include "constants.h"
#include "game_data.h"

constexpr unsigned char NUM_PLANTS = 4;

void gameStateInit(GameData gd) {
    int plantSpacing = WINDOW_WIDTH/(NUM_PLANTS+1);
    float xLocation = plantSpacing;
    for (int i = 0; i < NUM_PLANTS; i++) {
        std::cout << "plant1\n";
        generatePlant({xLocation, WINDOW_HEIGHT - 100}, PlantType::FLOWER, gd);
        xLocation += plantSpacing;
    }

    // playerFish = generateFish({(float)WINDOW_WIDTH/2, (float)WINDOW_HEIGHT/2});
    // fish.push_back(playerFish);
    std::cout << "finished\n";
}

void gameStateUpdates(GameData gd) {
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
    std::cout << "GameStateInit\n";
    gameStateInit(gd);

    double lastTick = 0.0;
    const double tickInterval = 0.1; // seconds between growth steps

    while (!WindowShouldClose()) {
        double now = GetTime();
        if (now - lastTick >= tickInterval) {
            std::cout << "GameStateupdates\n";
            gameStateUpdates(gd);
            lastTick = now;
        }
        // handleUserInput();
        drawWorld(gd.sprites);
    }

    CloseWindow();
    return 0;
}