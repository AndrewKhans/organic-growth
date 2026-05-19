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

float calculateMass(const FishBody& fb) {
    float mass = 0.0f;
    for (const FishPart &fp : fb.arr) {
        mass += fp == FishPart::AIR ? 0 : 1;
    }
    return mass;
}

unsigned int addFish(GameData &gd, Vector2 worldCoords) {
    unsigned int id = gd.nextEntityId++;

    FishBody fb = loadFishBody(id, "Fish1_Sprite.png");
    gd.fishBodies.push_back(fb);
    gd.idToFishBodyIdx[id] = gd.fishBodies.size()-1;

    Sprite s = loadSprite(id, "Fish1_Body.png");
    gd.sprites.push_back(s);
    gd.idToSpriteIdx[id] = gd.sprites.size()-1;

    PhysicsBody pb;
    pb.entityId = id;
    pb.mass = calculateMass(fb);
    pb.velocity = {0.0f, 0.0f};
    gd.physicsBodies.push_back(pb);
    gd.idToPhysicsBodyIdx[id] = gd.physicsBodies.size()-1;

    gd.idToWorldCoords[id] = worldCoords;
    return id;
}
