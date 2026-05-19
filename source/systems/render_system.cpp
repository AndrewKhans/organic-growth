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
Rotation

To go from the center to a pixel's location,
Dist from center to original point = sqrt(x*pixelsize^2 + y*pixelsize^2)
Dist from center to shifted point (dist') = sqrt(x'*pixelsize^2 + y'*pixelsize^2)
x component of displacement = sin(rotation)*dist'
y component of displacement = dist - dist'
.
|__.
| /
|/
*/
void drawSprite(const Sprite &s, const Vector2 &worldCoords) {
    Vector2 offset = {((float)s.width/2)*PIXEL_SIZE, ((float)s.height/2)*PIXEL_SIZE - PIXEL_SIZE};
    Rectangle pixel;
    pixel.height = PIXEL_SIZE;
    pixel.width = PIXEL_SIZE;
    // std::cout << "worldcoords: " << worldCoords.x << ", " << worldCoords.y << "\n";
    for (unsigned int y = 0; y < s.height; y++) {
        pixel.y = worldCoords.y - y*PIXEL_SIZE + offset.y;
        // todo: skip drawing this pixel if it's too high or low. end loop we're too low
        for (unsigned int x = 0; x < s.width; x++) {
            // todo: skip drawing this pixel if it's too far left or right. end inner loop
            // if too far right
            Color c = s.pixels[x + y*s.width];
            if IS_BLANK(c) continue;

            pixel.x = worldCoords.x + x*PIXEL_SIZE - offset.x;
            DrawRectanglePro(pixel, {0, 0}, 0, c);
        }
    }
}

void drawWorld(GameData &gd) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    for (const Sprite& s : gd.sprites) {
        const Vector2 &worldCoords = gd.idToWorldCoords[s.entityId];

        // Todo: skip if this sprite is fully offscreen
        drawSprite(s, worldCoords);
        // rippleSprite(s);
    }
    // unsigned int s = 90;
    // DrawRectangle((WINDOW_WIDTH/2) - s/2,
    //               (WINDOW_HEIGHT/2) - s/2,
    //               s, s, RED);

    // DrawRectangle((WINDOW_WIDTH/2) - 3/2,
    //               (WINDOW_HEIGHT/2) - 3/2,
    //               3, 3, BLUE);

    EndDrawing();
}
