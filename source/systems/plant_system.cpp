#include "systems/plant_system.h"
#include <iostream>

void update(unsigned int i, PlantBody pb, Sprite *s, PlantPart pp, Color c) {
    pb.arr[i] = pp;
    s->pixels[i] = c;
}

void generatePlant(Vector2 worldCoords, PlantType pt, GameData gd) {

    PlantBody pb;
    Sprite s;
    unsigned int id = gd.nextEntityId++;

    pb.entityId = id;
    s.entityId = id;

    pb.type = pt;
    pb.worldCoords = worldCoords;
    s.worldCoords  = worldCoords;

    pb.arr.resize(pb.width*pb.height, PlantPart::AIR);
    std::cout << "resize 1\n";
    s.pixels.resize(s.width*s.height, BLANK);
    std::cout << "resize 2\n";
    std::vector<unsigned int> vect;
    vect.resize(60*60, 100);
    std::cout << "done\n";

    update(pb.width*0 + (int)pb.width/2, pb, &s, PlantPart::SEED, BROWN);

    pb.growthLoc = {(int)pb.width/2, 0};

    pb.stemColor = {30, 120, 60, 255};
    pb.petalColor.r = randInt(0,255);
    pb.petalColor.g = randInt(0,255);
    pb.petalColor.b = randInt(0,255);
    pb.petalColor.a = 255;

    std::cout << "1\n";

    gd.plantBodies.push_back(pb);
    std::cout << "2\n";
    gd.sprites.push_back(s);
    std::cout << "3\n";
    // static_assert(gd.idToSprite.find(id) == -1);
    gd.idToSprite[id] = &s;
}

void growSprout(PlantBody& pb, Sprite* s) {
    update(pb.growthLoc.y*pb.width + pb.growthLoc.x, pb, s, PlantPart::STEM, pb.stemColor);
    pb.growthLoc.y += 1;

    // Stem shift
    if (pb.growthLoc.y > 1 &&
        pb.arr[(pb.growthLoc.y-1)*pb.width + pb.growthLoc.x] != PlantPart::AIR &&
        pb.arr[(pb.growthLoc.y-2)*pb.width + pb.growthLoc.x] != PlantPart::AIR &&
        randInt(0,6) == 0) {

        int offset = randInt(0,1) == 0 ? 1 : -1;
        pb.growthLoc.x += offset;
    }
}

void growFlowering(PlantBody& pb, Sprite* s) {
    update(pb.growthLoc.y*pb.width + pb.growthLoc.x, pb, s, PlantPart::PETAL, pb.petalColor);
}

void growFlower(PlantBody& pb, Sprite *s) {
    switch (pb.growthPhase) {
        case GrowthPhase::SEED:
            break;
        case GrowthPhase::SPROUT:
            growSprout(pb, s);
            break;
        case GrowthPhase::FLOWERING:
            growFlowering(pb, s);
            break;
        case GrowthPhase::DORMANT:
            break;
        default:
            throw std::runtime_error("Unexpected growth phase");
    }
}

void updateAge(PlantBody& pb) {
    switch (pb.growthPoints) {
        case 5:
            pb.growthPoints += randInt(0,5);
            pb.growthPhase = GrowthPhase::SPROUT;
            break;
        case 20:
            pb.growthPoints += randInt(0,5);
            pb.growthPhase = GrowthPhase::FLOWERING;
            break;
        default: // Seed phase
            break;
    }
    pb.growthPoints++;
}

void growPlants(GameData gd) {
    for (auto& pb : gd.plantBodies) {
        Sprite *s = gd.idToSprite[pb.entityId];
        switch (pb.type) {
            case PlantType::FLOWER:
                growFlower(pb, s);
                break;
            case PlantType::ALGAE:
                break;
        }
        updateAge(pb);
    }
}



// // Find the coordinates of each petal's base
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
