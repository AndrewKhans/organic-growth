#include "flower.h"
// #include "constants.h"
#include <iostream>
#include <vector>
#include <random>

int randInt(int min, int max) {
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(rng);
}

Flower::Flower(coordPair loc) {
    this->loc = loc;

    plantArr.resize(10, std::vector<plantPart>(50, AIR));

    plantArr[(int)plantArr.size()/2][0] = SEED;
    growthPoint = {(int)plantArr.size()/2, 0};

    // Assign random birth traits
    // TODO: Make these random
    petalColor.r = 60;
    petalColor.g = 60;
    petalColor.b = 120;
    petalColor.a = 120;

    stemColor.r = 30;
    stemColor.g = 120;
    stemColor.b = 60;
    stemColor.a = 255;

    maxHeight = 5;
}

void Flower::grow() {
    std::cout << "Flower age: " << age << "\n";

    switch (growthPhase) {
        case SEEDLING:
            // std::cout << "Seedling grow\n";
            if (age > 4) growthPhase = LEAFY;
            break;
        case LEAFY:
            // std::cout << "Leafy grow\n";
            plantArr[growthPoint.x][growthPoint.y] = STEM;
            growthPoint.y += 1;
            if (randInt(0,4) == 0) {
                int offset = randInt(0,1) == 0 ? 1 : -1;
                growthPoint.x += offset;
            }
            if (age > 20) growthPhase = FLOWER;
            break;
        case FLOWER:
            // std::cout << "Flower grow\n";
            plantArr[growthPoint.x][growthPoint.y] = PETAL;
            break;
    }
    age += 1;
}

void Flower::draw() {

    for (unsigned int arr_y = 0; arr_y < plantArr[0].size(); arr_y++) {
        for (unsigned int arr_x = 0; arr_x < plantArr.size(); arr_x++) {
            plantPart p = plantArr[arr_x][arr_y];
            if (p == AIR) continue;

            Color c;
            switch (p) {
                case AIR: break;
                case SEED:
                    c = BROWN;
                    break;
                case STEM:
                    c = stemColor;
                    break;
                case LEAF:
                case LEAFBASE:
                    c = stemColor;
                    break;
                case PETALBASE:
                    c = BROWN;
                    break;
                case PETAL:
                    c = petalColor;
                    break;
            }

            int x = loc.x + (arr_x-(int)plantArr.size()/2)*PIXEL_SIZE;
            int y = loc.y - arr_y*PIXEL_SIZE;
            DrawRectangle(x, y, PIXEL_SIZE, PIXEL_SIZE, c);
        }
    }
}

// Find the coordinates of each petal's base
// static Vector2 *findPetalBases(flower_t f) {
//     float angleBetweenPetals;
//     Vector2 petalCoords[f.petalCount];

//     // This is the problem of finding x equally spaced points along a circle
//     angleBetweenPetals = (2*PI)/f.petalCount;

//     currAngle = 0.0f; // TODO: Start petals at a random point on the seedHead
//     for (unsigned char i; i < f.petalCount; i++) {

//         // The polar coordinate of each petal in sequence `i` is `(seedHeadRadius, i*angleBetweenPetals)`
//         // The cartesian coordinates of each petal are
//         petalCoords[i].x = f.seedHeadRadius * math.cos(angleBetweenPetals);
//         petalCoords[i].y = f.seedHeadRadius * math.sin(angleBetweenPetals);

//     }
// }

// void draw() {
//     Vector2 stemPiece;
//     Vector2 drawHead;

//     stemPiece.x = f.stemPieceSize;
//     stemPiece.y = f.stemPieceSize;

//     drawHead.x = seedLoc.x;
//     drawHead.y = seedLoc.y;

//     // Draw Stem
//     drawHead.x -= f.stemPieceSize/2; // center each stem piece above seed
//     for (unsigned int i = 0; i < f.stemSegments; i++) {
//         DrawRectangleV(drawHead, stemPiece, f.stemColor);
//         drawHead.y -= f.stemPieceSize;
//     }
//     drawHead.x = seedLoc.x; // re-center drawhead over seed

//     // Draw seed head
//     DrawCircleV(drawHead, f.seedHeadRadius, f.seedHeadColor);

//     // Draw petals

//     // Find locations of petalCount points along seedHead

//     // for (unsigned char i = 0; i < f.petalCount; i++) {
//     //     DrawEllipse(drawHead.x, drawHead.y, f.petalLength, f.petalLength/2, f.petalColor);
//     //     drawHead.x += 10;
//     // }
//     // RLAPI void DrawEllipse(int centerX, int centerY, float radiusH, float radiusV, Color color);             // Draw ellipse

// }
