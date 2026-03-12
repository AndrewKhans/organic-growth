#include "raylib.h"
#include "plant_system.h"
#include "constants.h"
#include <chrono>
#include <thread>

constexpr unsigned char NUM_PLANTS = 4;

int main(void)
{

    std::vector<Plant> plants;

    int plantSpacing = WINDOW_SIZE_X/(NUM_PLANTS+1);
    int xLocation = plantSpacing;
    for (int i = 0; i < NUM_PLANTS; i++) {
        plants.push_back(generateFlower({xLocation, WINDOW_SIZE_Y - 100}));
        xLocation += plantSpacing;
    }

    InitWindow(WINDOW_SIZE_X, WINDOW_SIZE_Y, "organic-growth");

    while (!WindowShouldClose()) {

        // Game state updates
        growPlants(plants);


        // Draw everything
        BeginDrawing();

            ClearBackground(RAYWHITE);
            drawPlants(plants);

        EndDrawing();

        // Todo: Make this sleep based on how long it took the rest of the stuff to happen
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    CloseWindow();
    return 0;
}