#include "raylib.h"
#include "flower.h"

#define WINDOW_SIZE_X 400
#define WINDOW_SIZE_Y 400

int main(void)
{
    flower_t f;
    Vector2 seedLocation;

    seedLocation.x = 200.0f;
    seedLocation.y = (float)WINDOW_SIZE_Y - 100;

    InitWindow(WINDOW_SIZE_X, WINDOW_SIZE_Y, "organic-growth");

    while (!WindowShouldClose()) {

        BeginDrawing();

            ClearBackground(RAYWHITE);
            
            f = generateFlower();
            drawFlower(seedLocation, f);
        
        EndDrawing();

    }

    CloseWindow();
    return 0;
}