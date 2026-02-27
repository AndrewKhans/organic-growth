#include "raylib.h"

int main(void)
{
    InitWindow(800, 450, "test");

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("it works", 190, 200, 20, BLACK);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}