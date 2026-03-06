#include "raylib.h"
#include "flower.h"
#include "constants.h"
#include <chrono>
#include <thread>


int main(void)
{
    coordPair seedLocation;

    seedLocation.x = WINDOW_SIZE_X/2;
    seedLocation.y = WINDOW_SIZE_Y - 100;

    Flower f(seedLocation);

    InitWindow(WINDOW_SIZE_X, WINDOW_SIZE_Y, "organic-growth");

    unsigned int i = 0;
    while (!WindowShouldClose()) {

        // Game state updates
        f.grow();

        i++;
        if (i > 40) {
            f = Flower(seedLocation);
            i = 0;
        }

        // Draw everything
        BeginDrawing();

            ClearBackground(RAYWHITE);
            DrawRectangle(seedLocation.x, seedLocation.y, 10, 10, BLACK);
            f.draw();

        EndDrawing();

        // Todo: Make this sleep based on how long it took the rest of the stuff to happen
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    CloseWindow();
    return 0;
}