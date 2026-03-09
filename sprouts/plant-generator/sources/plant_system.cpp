#include "plant_system.h"
#include <iostream>
#include <vector>
#include <random>

int randInt(int min, int max) {
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(rng);
}

Plant generateFlower(CoordPair seedLocation) {
    Plant p;

    p.type = FLOWER;
    p.loc = seedLocation;
    p.growthPoint = seedLocation;
    std::cout << "size of plantArr" << p.plantArr.size() << "\n";
    p.plantArr.resize(p.arrWidth*p.arrHeight, AIR);

    p.plantArr[p.arrWidth*0 + (int)p.arrWidth/2] = SEED;
    p.growthPoint = {(int)p.arrWidth/2, 0};

    // Assign random birth traits
    // TODO: Make these random
    p.petalColor.r = 60;
    p.petalColor.g = 60;
    p.petalColor.b = 120;
    p.petalColor.a = 120;

    p.stemColor.r = 30;
    p.stemColor.g = 120;
    p.stemColor.b = 60;
    p.stemColor.a = 255;

    return p;
}

void growPlants(std::vector<Plant> &plants) {
    for (auto& p : plants) {
        switch (p.growthPhase) {

            case SEEDLING:
                if (p.age > 1 && randInt(0,4) == 0 ||
                    p.age > 6) {
                        p.growthPhase = SPROUT;
                        p.age = 0;
                    }
                break;
            case SPROUT:
                p.plantArr[p.growthPoint.x + p.growthPoint.y*p.arrWidth] = STEM;
                p.growthPoint.y += 1;

                // Stem shift
                if (p.growthPoint.y > 1 &&
                    p.plantArr[p.growthPoint.x + (p.growthPoint.y-1)*p.arrWidth] != AIR &&
                    p.plantArr[p.growthPoint.x + (p.growthPoint.y-2)*p.arrWidth] != AIR &&
                    randInt(0,4) == 0) {

                    int offset = randInt(0,1) == 0 ? 1 : -1;
                    p.growthPoint.x += offset;
                }

                if (p.age > 5 && randInt(0,3) == 0 ||
                    p.age > 15) {
                        p.growthPhase = FLOWERING;
                        p.age = 0;
                    }
                break;
            case FLOWERING:
                p.plantArr[p.growthPoint.x + p.growthPoint.y*p.arrWidth] = PETAL;
                p.growthPhase = DORMANT;
                break;
            case DORMANT:
                // Regrow if needed
                break;
        }
        p.age += 1;
    }
}

void drawPlants(std::vector<Plant> &plants) {
    for (const auto& p : plants) {
        for (unsigned int arr_y = 0; arr_y < p.arrHeight; arr_y++) {
            for (unsigned int arr_x = 0; arr_x < p.arrWidth; arr_x++) {
                PlantPart part = p.plantArr[arr_x + arr_y*p.arrWidth];
                if (part == AIR) continue;

                Color c;
                switch (part) {
                    case AIR: break;
                    case SEED:
                        c = BROWN;
                        break;
                    case STEM:
                        c = p.stemColor;
                        break;
                    case LEAF:
                    case LEAFBASE:
                        c = p.stemColor;
                        break;
                    case PETALBASE:
                        c = BROWN;
                        break;
                    case PETAL:
                        c = p.petalColor;
                        break;
                }

                int x = p.loc.x + (arr_x-(int)p.arrWidth/2)*PIXEL_SIZE;
                int y = p.loc.y - arr_y*PIXEL_SIZE;
                DrawRectangle(x, y, PIXEL_SIZE, PIXEL_SIZE, c);
            }
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
