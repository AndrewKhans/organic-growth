#include "systems/fish_system.h"
#include "asset_loader.h"
#include <iostream>

// Debug functions
void printFishBody(const FishBody& fb) {
    for (unsigned int y = 0; y < fb.height; y++) {
        for (unsigned int x = 0; x < fb.width; x++) {
            FishPart fp = fb.arr[y*fb.height + x];
            std::cout << (fp == FishPart::AIR ? 0 : 1);
        }
        std::cout << "\n";
    }
}

void update(unsigned int i, FishBody &fb, Sprite &s, FishPart fp, Color c) {
    fb.arr[i] = fp;
    s.pixels[i] = c;
}

unsigned int generateFish(GameData &gd, Vector2 worldCoords) {
    FishBody fb;
    Sprite s;
    unsigned int id = gd.nextEntityId++;

    fb.entityId = id;
    s.entityId = id;

    fb.worldCoords = worldCoords;
    s.worldCoords = worldCoords;

    fb.arr.resize(fb.width*fb.height, FishPart::AIR);
    s.pixels.resize(s.width*s.height, BLANK);

    gd.sprites.push_back(s);
    gd.fishBodies.push_back(fb);
    gd.idToFishBodyIdx[id] = gd.fishBodies.size()-1;
    gd.idToSpriteIdx[id] = gd.sprites.size()-1;

    return id;
}
