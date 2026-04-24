#include "raylib.h"
#include "game_objects/plant_system.h"
#include "game_objects/fish_system.h"
#include "constants.h"
#include <chrono>
#include <thread>

constexpr unsigned char NUM_PLANTS = 4;

std::vector<Plant> plants;
std::vector<Fish> fish;
Fish playerFish;

void gameStateInit() {
    int plantSpacing = WINDOW_WIDTH/(NUM_PLANTS+1);
    float xLocation = plantSpacing;
    for (int i = 0; i < NUM_PLANTS; i++) {
        plants.push_back(generatePlant({xLocation, WINDOW_HEIGHT - 100}, PlantType::FLOWER));
        xLocation += plantSpacing;
    }

    playerFish = generateFish({(float)WINDOW_WIDTH/2, (float)WINDOW_HEIGHT/2 });
    fish.push_back(playerFish);
}

void gameStateUpdates() {
    growPlants(plants);
}

void handleUserInput() {
    if (IsKeyDown(KEY_RIGHT)) playerFish.worldCoords.x += 2.0f;
    if (IsKeyDown(KEY_LEFT))  playerFish.worldCoords.x -= 2.0f;
    if (IsKeyDown(KEY_UP))    playerFish.worldCoords.y -= 2.0f;
    if (IsKeyDown(KEY_DOWN))  playerFish.worldCoords.y += 2.0f;
}

void drawFrame() {
    BeginDrawing();

    ClearBackground(RAYWHITE);

    drawPlants(plants);
    drawFish(fish);

    EndDrawing();
}

int main(void)
{
    gameStateInit();
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "organic-growth");

    while (!WindowShouldClose()) {
        gameStateUpdates();
        handleUserInput();
        drawFrame();

        // Todo: Make this sleep based on how long it took the rest of the stuff to happen
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    CloseWindow();
    return 0;
}