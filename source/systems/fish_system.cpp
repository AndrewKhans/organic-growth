#include "systems/fish_system.h"

#include <iostream>

void update(unsigned int i, FishBody &fb, Sprite &s, FishPart fp, Color c) {
    fb.arr[i] = fp;
    s.pixels[i] = c;
}

float calculateMass(const FishBody& fb) {
    float mass = 0.0f;
    for (const FishPart &fp : fb.arr) {
        switch (fp) {
            case FishPart::AIR:
                break;
            case FishPart::BODY:
                mass += 1;
                break;
            case FishPart::MOUTH:
                mass += 1;
                break;
            case FishPart::FIN:
                mass += 0.5;
                break;
            default:
                std::cout << "Unrecognized fish part:\n";
                exit(1);
        }
    }
    return mass;
}

float calculateSwimForce(const FishBody& fb) {
    float swimForce = 0;
    for (const FishPart &fp : fb.arr) {
        swimForce += fp == FishPart::FIN ? 3 : 0;
    }
    return swimForce;
}

Vector2 calculateMouthLocation(FishBody &fb) {
    unsigned int count = 0;
    unsigned int xSum = 0, ySum = 0;
    for (unsigned int i = 0; i < fb.arr.size(); i++) {
        const FishPart &fp = fb.arr[i];
        if (fp == FishPart::MOUTH) {
            xSum += i % FISH_BODY_SIZE;
            ySum += (unsigned int)i/FISH_BODY_SIZE;
            count++;
        }
    }

    float avgX = (float)xSum/count;
    float avgY = (float)ySum/count + 2;

    return {avgX, avgY};
}

/*

*/
void collideFish(Vector2 mouthLoc1, FishBody &fb1, Transform2 &t1, PhysicsBody &pb1,
                                    FishBody &fb2, Transform2 &t2, PhysicsBody &pb2) {

    // Calculate worldCoords of each pixel in fish2, saving the nearest one
    unsigned int minDistance = (fb1.height/2)*PIXEL_SIZE;
    FishPart collidedPart;

    for (unsigned int y = 0; y < fb2.height; y++) {
        for (unsigned int x = 0; x < fb2.width; x++) {
            FishPart part = fb2.arr[x + y*fb2.width];
            if (part == FishPart::AIR) continue;

            Vector2 partLoc = localToWorldCoords({(float)x, (float)y}, {(float)fb2.width, (float)fb2.height}, t2);
            float dist = dist2d(mouthLoc1, partLoc);
            if (dist < minDistance) {
                collidedPart = part;
                minDistance = dist;
            }
        }
    }

    // Fish are not close enough: no collision
    if (minDistance >= 60) return;

    if (collidedPart == FishPart::MOUTH) {
        // Two mouths collide: bounce off
        std::cout << "Collided with mouth\n";
        Vector2 force1 = rotationToUnitVector(t1.rot);
        Vector2 force2 = rotationToUnitVector(t2.rot);

        float f = 1000;
        force1.x *= f; force1.y *= f; force2.x *= f; force2.y *= f;

        applyForce(pb1, force1);
        applyForce(pb2, force2);
    } else {
        // Bite!
        std::cout << "Collided with body\n";

    }
}

void checkForCollisionsWithOtherFish(GameData &gd, FishBody &fb1, unsigned int fishBodyIdx) {
    unsigned int id1 = fb1.entityId;
    Transform2 &t1 = gd.idToTransform2[id1];
    PhysicsBody &pb1 = gd.physicsBodies[gd.idToPhysicsBodyIdx[id1]];
    Vector2 mouth1WorldCoords = localToWorldCoords(fb1.mouthLocation, {(float)fb1.width, (float)fb1.height}, t1);
    DrawRectangleV({mouth1WorldCoords.x - 5, mouth1WorldCoords.y - 5}, {10,10}, BLUE);

    for (unsigned int j = fishBodyIdx+1; j < gd.fishBodies.size(); j++) {
        FishBody &fb2 = gd.fishBodies[j];
        unsigned int id2 = fb2.entityId;
        Transform2 &t2 = gd.idToTransform2[id2];
        PhysicsBody &pb2 = gd.physicsBodies[gd.idToPhysicsBodyIdx[id2]];

        // std::cout << "fish1 mouth: " << mouth1WorldCoords.x << ", " << mouth1WorldCoords.y << " fish2 transform: " << t2.x << ", " << t2.y << "\n";
        if (dist2d(mouth1WorldCoords, {t2.x, t2.y}) < ((fb1.height/2)*PIXEL_SIZE)) {
            collideFish(mouth1WorldCoords, fb1, t1, pb1, fb2, t2, pb2);
            break;
        }
    }
}


void handleFishCollisions(GameData &gd) {
    for (unsigned int i = 0; i < gd.fishBodies.size()-1; i++) {
        FishBody &fb = gd.fishBodies[i];
        checkForCollisionsWithOtherFish(gd, fb, i);
    }
}

// Must be called whenever the fish body changes
void updateFishValues(FishBody &fb, PhysicsBody &pb) {
    pb.mass = calculateMass(fb);
    fb.swimForce = calculateSwimForce(fb);
    fb.mouthLocation = calculateMouthLocation(fb);
}

unsigned int addFish(GameData &gd, Transform2 t) {
    unsigned int id = gd.nextEntityId++;

    FishBody fb = loadFishBody(id, "Fish1_Body.png");
    Sprite s = loadSprite(id, "Fish1_Sprite.png");

    PhysicsBody pb;
    pb.entityId = id;
    pb.velocity = {0.0f, 0.0f};

    updateFishValues(fb, pb);

    gd.fishBodies.push_back(fb);
    gd.idToFishBodyIdx[id] = gd.fishBodies.size()-1;

    gd.sprites.push_back(s);
    gd.idToSpriteIdx[id] = gd.sprites.size()-1;

    gd.physicsBodies.push_back(pb);
    gd.idToPhysicsBodyIdx[id] = gd.physicsBodies.size()-1;

    gd.idToTransform2[id] = t;
    return id;
}
