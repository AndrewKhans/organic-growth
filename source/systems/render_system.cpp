#include "raylib.h"
#include "render_system.h"
#include "constants.h"
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
    unsigned int startX = s.worldCoords.x - ((unsigned int)s.width/2)*PIXEL_SIZE;

    Vector2 drawPos;
    for (unsigned int y = 0; y < s.height; y++) {
        drawPos.y = s.worldCoords.y - y*PIXEL_SIZE;
        // todo: skip drawing this pixel if it's too high or low. end loop we're too low
        for (unsigned int x = 0; x < s.width; x++) {
            // todo: skip drawing this pixel if it's too far left or right. end inner loop
            // if too far right
            Color c = s.pixels[x + y*s.width];
            if IS_BLANK(c) continue;

            drawPos.x = startX + x*PIXEL_SIZE;
            DrawRectangleV(drawPos, {PIXEL_SIZE, PIXEL_SIZE}, c);
        }
    }
}

void drawWorld(const std::vector<Sprite>& sprites) {

    BeginDrawing();

    ClearBackground(RAYWHITE);

    for (const auto& s : sprites) {
        // Todo: detect if this sprite is fully offscreen
        drawSprite(s);
    }

    EndDrawing();
}
