#include "raylib.h"
#include "render_system.h"
#include <iostream>

#define IS_BLANK(x) ((x).r == 0 && (x).g == 0 && (x).b == 0 && (x).a == 0)

// Debug Functions
void printSprite(const Sprite& s) {
    for (unsigned int y = 0; y < s.height; y++) {
        for (unsigned int x = 0; x < s.width; x++) {
            Color c = s.pixels[x + y*s.width];
            char p = IS_BLANK(c) ? ' ' : '1';
            std::cout << p;
        }
        std::cout << "\n";
    }
}

void drawSprite(const Sprite& s) {
    std::cout << "\n";
    printSprite(s);
    for (unsigned int y = 0; y < s.height; y++) {
        for (unsigned int x = 0; x < s.width; x++) {
            Color c = s.pixels[x + y*s.width];
            if IS_BLANK(c) continue;

            int draw_x = s.worldCoords.x + (x-(int)s.width/2)*PIXEL_SIZE;
            int draw_y = s.worldCoords.y - y*PIXEL_SIZE;
            DrawRectangle(draw_x, draw_y, PIXEL_SIZE, PIXEL_SIZE, c);
        }
    }
}

void drawWorld(const std::vector<Sprite>& sprites) {

    BeginDrawing();

    ClearBackground(RAYWHITE);

    for (const auto& s : sprites) {
        drawSprite(s);
    }

    EndDrawing();

}
