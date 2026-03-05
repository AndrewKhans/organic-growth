#include "raylib.h"
#include "flower.h"
#include <unistd.h>

#define WINDOW_SIZE_X 400
#define WINDOW_SIZE_Y 400

int main(void)
{
    Vector2 seedLocation;

    seedLocation.x = 200.0f;
    seedLocation.y = (float)WINDOW_SIZE_Y - 100;

    Flower f(Vector2{10, 20});

    InitWindow(WINDOW_SIZE_X, WINDOW_SIZE_Y, "organic-growth");

    while (!WindowShouldClose()) {

        // Game state updates
        f.grow();

        // Draw everything
        BeginDrawing();

            ClearBackground(RAYWHITE);
            f.draw();

        EndDrawing();

        sleep(1);
    }

    CloseWindow();
    return 0;
}