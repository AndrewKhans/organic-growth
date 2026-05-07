#include "raylib.h"
#include "render_system.h"

#define IS_BLANK(x) ((x).r == 0 && (x).g == 0 && (x).b == 0 && (x).a == 0)

void drawSprite(const Sprite& s) {
    for (unsigned int arr_y = 0; arr_y < s.height; arr_y++) {
        for (unsigned int arr_x = 0; arr_x < s.width; arr_x++) {
            Color c = s.pixels[arr_x + arr_y*s.width];
            if IS_BLANK(c) continue;

            int draw_x = s.worldCoords.x + (arr_x-(int)s.width/2)*PIXEL_SIZE;
            int draw_y = s.worldCoords.y - arr_y*PIXEL_SIZE;
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
