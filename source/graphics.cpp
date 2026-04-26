#include <span>
#include "fish.h"
#include "plant.h"
#include "raylib.h"

// void draw

void drawWorld(std::vector<Fish>& fish, std::vector<Plant>& plants) {
    for (const auto& p : plants) drawSprite(p.sprite);
    for (const auto& f : fish) drawSprite(f.sprite);

}

void drawSprite(const std::vector<Color>& s) {
    Color c;
    Color empty = {0,0,0,0};

    for (unsigned int arr_y = 0; arr_y < s.arrHeight; arr_y++) {
        for (unsigned int arr_x = 0; arr_x < s.arrWidth; arr_x++) {
            c = p.plantArr[arr_x + arr_y*p.arrWidth];

            int x = p.worldCoords.x + (arr_x-(int)p.arrWidth/2)*PIXEL_SIZE;
            int y = p.worldCoords.y - arr_y*PIXEL_SIZE;
            DrawRectangle(x, y, PIXEL_SIZE, PIXEL_SIZE, c);
        }
    }
}