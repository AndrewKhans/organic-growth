#include <span>
#include "fish.h"
#include "plant.h"
#include "raylib.h"

void drawObjects(std::vector<Fish> fish, std::vector<Plant> plants) {
    for (const auto& p : plants) drawSprite(p.sprite);
    for (const auto& f : fish) drawSprite(f.sprite);

}

void drawSprite(std::span<Color> sprite) {
    Color c;

    for (const auto& p : plants) {
        for (unsigned int arr_y = 0; arr_y < p.arrHeight; arr_y++) {
            for (unsigned int arr_x = 0; arr_x < p.arrWidth; arr_x++) {
                part = p.plantArr[arr_x + arr_y*p.arrWidth];
                if (part == PlantPart::AIR) continue;

                switch (part) {
                    case PlantPart::AIR: break;
                    case PlantPart::SEED:
                        c = BROWN;
                        break;
                    case PlantPart::STEM:
                        c = p.stemColor;
                        break;
                    case PlantPart::LEAF:
                    case PlantPart::LEAFBASE:
                        c = p.stemColor;
                        break;
                    case PlantPart::PETALBASE:
                        c = BROWN;
                        break;
                    case PlantPart::PETAL:
                        c = p.petalColor;
                        break;
                }

                int x = p.worldCoords.x + (arr_x-(int)p.arrWidth/2)*PIXEL_SIZE;
                int y = p.worldCoords.y - arr_y*PIXEL_SIZE;
                DrawRectangle(x, y, PIXEL_SIZE, PIXEL_SIZE, c);
            }
        }
    }
}