#include "render_system.h"
#include <iostream>

// Debug Functions
void printSprite(const Sprite &s) {
    for (unsigned int y = 0; y < s.height; y++) {
        for (unsigned int x = 0; x < s.width; x++) {
            Color c = s.pixels[x + y*s.width];
            char p = IS_BLANK(c) ? ' ' : '1';
            std::cout << p;
        }
        std::cout << "\n";
    }
}

// Note: The coords you pass to DrawRectangle are the top left corner
// Draw a sprite, starting at the bottom left corner

/*
    Todo: Optimizations
        - Before the loop, use the X/Y and size to determine if we should even start the loop
        - Skip drawing a pixel if it's Y is too high or too low. End the loop if the current pixel is too low, as other
          pixels will definitely be too low. Apply the same logic to X
        - Try finding a line that pixels fall on and use that for placing them, instead of doing a rotation matrix
          for each
        - Try rotating all pixels at the same time using matrix multiplication with a rotation matrix
*/
void drawSprite(const Sprite &s, const Transform2 &t) {
    Rectangle pixel;
    pixel.width = PIXEL_SIZE;
    pixel.height = PIXEL_SIZE;

    Vector2 offset = {((float)s.width/2)*PIXEL_SIZE - PIXEL_SIZE/2, ((float)s.height/2)*PIXEL_SIZE - PIXEL_SIZE/2};
    float rot = t.rot - 180;
    float rads = rot * (PI / 180);
    for (unsigned int y = 0; y < s.height; y++) {
        float yCoord = y*PIXEL_SIZE - offset.y;
        for (unsigned int x = 0; x < s.width; x++) {
            Color c = s.pixels[x + y*s.width];
            if IS_BLANK(c) continue;

            float xCoord = x*PIXEL_SIZE - offset.x;
            pixel.x = t.x + (xCoord*cosf(rads) - yCoord*sinf(rads));
            pixel.y = t.y + (xCoord*sinf(rads) + yCoord*cosf(rads));
            DrawRectanglePro(pixel, {PIXEL_SIZE/2, PIXEL_SIZE/2}, rot, c);
        }
    }
}

void drawWorld(GameData &gd) {
    BeginDrawing();
    ClearBackground(BEIGE);

    for (const Sprite& s : gd.sprites) {
        const Transform2 &t = gd.idToTransform2[s.entityId];

        drawSprite(s, t);
        // Todo: implement rippling
        // rippling includes having the body shimmer, and having the body shift slightly left-right along axis
        // rippleSprite(s);

    }

    EndDrawing();
}
