#include "flower.h"
#include <iostream>
#include <vector>


Flower::Flower(Vector2 loc) {
    this->loc = loc;
    growthPoint = loc;

    plantArr.resize(10, std::vector<PlantPart>(10, AIR));

    plantArr[0][5] = SEED;

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
    std::cout << "\nFlower age: " << age << "\n";

    switch (growthPhase) {
        case SEEDLING:
            std::cout << "Seedling grow\n";
            if (age >= 10) growthPhase = LEAFY;
            break;
        case LEAFY:
            std::cout << "Leafy grow\n";
            if (age >= 20) growthPhase = FLOWER;
            break;
        case FLOWER:
            std::cout << "Flower grow\n";
            break;
    }
    age += 1;
}

void Flower::draw() {

    // Set drawHead to the graphics-coords location of (0,0) in plantArr
    Vector2 drawHead = loc - (int)plantArr[0].size()/2

    std::cout << "Drawing flower\n";
    for (const std::vector<PlantPart>& row : plantArr) {
        for (const PlantPart part : row) {
            drawHead.x += 1;
            if (part == AIR) continue;

            Color c;
            switch (part) {
                case SEED:
                    c = BROWN;
                    break;
                case STEM:
                    c = stemColor;
                    break;
                case LEAF:
                    c = leafColor;
                    break;
                case PETAL:
                    c = petalColor;
                    break;
            }
            DrawRectangleV(drawHead, stemPiece, f.stemColor);

        }
        drawHead.y += 1;
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
