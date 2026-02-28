#include "raylib.h"

typedef struct {
    unsigned char petalCount;
    float petalLength;
    Color petalColor;

    unsigned int stemSegments;
    float stemPieceSize;
    Color stemColor;

    float seedHeadRadius;
    Color seedHeadColor;
} flower_t;

flower_t generateFlower();

void drawFlower(Vector2 seedLoc, flower_t f);

