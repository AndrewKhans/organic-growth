#include "raylib.h"
#include "plant_system.h"
#include "constants.h"
#include <chrono>
#include <thread>

constexpr unsigned char NUM_PLANTS = 4;

Vector2 playerCoords = { (float)WINDOW_WIDTH/2, (float)WINDOW_HEIGHT/2 };

void handleUserInput() {
    if (IsKeyDown(KEY_RIGHT)) playerCoords.x += 2.0f;
    if (IsKeyDown(KEY_LEFT))  playerCoords.x -= 2.0f;
    if (IsKeyDown(KEY_UP))    playerCoords.y -= 2.0f;
    if (IsKeyDown(KEY_DOWN))  playerCoords.y += 2.0f;
}

void drawFrame() {
    BeginDrawing();

    ClearBackground(RAYWHITE);
    drawPlants(plants);
    DrawCircleV(ballPosition, 50, MAROON);

    EndDrawing();
}

int main(void)
{

    std::vector<Plant> plants;

    int plantSpacing = WINDOW_WIDTH/(NUM_PLANTS+1);
    int xLocation = plantSpacing;
    for (int i = 0; i < NUM_PLANTS; i++) {
        plants.push_back(generateFlower({xLocation, WINDOW_HEIGHT - 100}));
        xLocation += plantSpacing;
    }

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "organic-growth");

    while (!WindowShouldClose()) {

        growPlants(plants);

        handleUserInput();

        drawFrame();

        // Todo: Make this sleep based on how long it took the rest of the stuff to happen
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    CloseWindow();
    return 0;
}