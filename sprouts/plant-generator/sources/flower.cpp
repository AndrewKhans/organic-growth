#include "flower.h"
#include <stdio.h>
#include <math.h>

/*
    Should this store the location of petalHead when it generates?

*/
flower_t generateFlower() {

    flower_t f;
    Color pc;
    Color sc;

    pc.r = 60;
    pc.g = 60;
    pc.b = 120;
    pc.a = 255;

    sc.r = 30;
    sc.g = 120;
    sc.b = 60;
    sc.a = 255;

    // Assign fields of f
    f.petalCount     = 1;
    f.stemSegments   = 10;
    f.stemPieceSize  = 10.0f;
    f.seedHeadRadius = 12.0f;
    f.petalLength    = 20.0f;
    f.seedHeadColor  = DARKBROWN;
    f.petalColor     = WHITE;
    f.petalColor     = pc;
    f.stemColor      = sc;
    return f;
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

void drawFlower(Vector2 seedLoc, flower_t f) {
    Vector2 stemPiece;
    Vector2 drawHead;

    stemPiece.x = f.stemPieceSize;
    stemPiece.y = f.stemPieceSize;

    drawHead.x = seedLoc.x;
    drawHead.y = seedLoc.y;

    // Draw Stem
    drawHead.x -= f.stemPieceSize/2; // center each stem piece above seed
    for (unsigned int i = 0; i < f.stemSegments; i++) {
        DrawRectangleV(drawHead, stemPiece, f.stemColor);
        drawHead.y -= f.stemPieceSize;
    }
    drawHead.x = seedLoc.x; // re-center drawhead over seed

    // Draw seed head
    DrawCircleV(drawHead, f.seedHeadRadius, f.seedHeadColor);

    // Draw petals
    
    // Find locations of petalCount points along seedHead

    // for (unsigned char i = 0; i < f.petalCount; i++) {
    //     DrawEllipse(drawHead.x, drawHead.y, f.petalLength, f.petalLength/2, f.petalColor);
    //     drawHead.x += 10;
    // }
    // RLAPI void DrawEllipse(int centerX, int centerY, float radiusH, float radiusV, Color color);             // Draw ellipse

}
