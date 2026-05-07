#include "systems/fish_system.h"
#include <iostream>

void update(unsigned int i, FishBody fb, Sprite *s, FishPart fp, Color c) {
    fb.arr[i] = fp;
    s->pixels[i] = c;
}

void generateFish(Vector2 worldCoords, GameData gd){
    FishBody fb;
    Sprite s;
    unsigned int id = gd.nextEntityId++;

    fb.entityId = id;
    s.entityId = id;

    fb.worldCoords = worldCoords;
    s.worldCoords = worldCoords;

    fb.arr.resize(fb.width*fb.height, FishPart::AIR);
    s.pixels.resize(s.width*s.height, BLANK);

    int i = (int)fb.width/2;
    update(i-1, fb, &s, FishPart::BODY, BROWN);
    update(i, fb, &s, FishPart::BODY, BROWN);
    update(i+1, fb, &s, FishPart::BODY, BROWN);

    gd.fishBodies.push_back(fb);
    gd.sprites.push_back(s);
    gd.idToSprite[id] = &s;
}
