#include "plant_system.h"
#include <iostream>


Plant generatePlant(Vector2 worldCoords, PlantType pt) {
    Plant p;

    p.type = pt;
    p.worldCoords = worldCoords;

    p.plantArr.resize(PLANT_ARR_WIDTH*PLANT_ARR_HEIGHT, PlantPart::AIR);
    p.plantArr[PLANT_ARR_WIDTH*0 + (int)PLANT_ARR_WIDTH/2] = PlantPart::SEED;
    p.growthLoc = {(int)PLANT_ARR_WIDTH/2, 0};

    // Assign random birth traits
    p.stemColor.r = 30;
    p.stemColor.g = 120;
    p.stemColor.b = 60;
    p.stemColor.a = 255;

    p.petalColor.r = randInt(0,255);
    p.petalColor.g = randInt(0,255);
    p.petalColor.b = randInt(0,255);
    p.petalColor.a = 255;

    return p;
}

void growSprout(Plant& p) {
    p.plantArr[p.growthLoc.x + p.growthLoc.y*PLANT_ARR_WIDTH] = PlantPart::STEM;
    p.growthLoc.y += 1;

    // Stem shift
    if (p.growthLoc.y > 1 &&
        p.plantArr[p.growthLoc.x + (p.growthLoc.y-1)*PLANT_ARR_WIDTH] != PlantPart::AIR &&
        p.plantArr[p.growthLoc.x + (p.growthLoc.y-2)*PLANT_ARR_WIDTH] != PlantPart::AIR &&
        randInt(0,6) == 0) {

        int offset = randInt(0,1) == 0 ? 1 : -1;
        p.growthLoc.x += offset;
    }
}

void growFlowering(Plant& p) {
    p.plantArr[p.growthLoc.x + p.growthLoc.y*PLANT_ARR_WIDTH] = PlantPart::PETAL;
}

void growFlower(Plant& p) {
    switch (p.growthPhase) {
        case GrowthPhase::SEED:
            break;
        case GrowthPhase::SPROUT:
            growSprout(p);
            break;
        case GrowthPhase::FLOWERING:
            growFlowering(p);
            break;
        case GrowthPhase::DORMANT:
            break;
        default:
            throw std::runtime_error("Unexpected growth phase");
    }
}

void growTree(Plant& p) {
    switch (p.growthPhase) {
        case GrowthPhase::SEED:
            break;
        case GrowthPhase::SPROUT:
            growSprout(p);
            break;
        case GrowthPhase::BARKY:
            break;
        case GrowthPhase::DORMANT:
            break;
        default:
            throw std::runtime_error("Unexpected growth phase");
    }
}

void updateAge(Plant& p) {
    switch (p.growthPoints) {
        case 5:
            p.growthPoints += randInt(0,5);
            p.growthPhase = GrowthPhase::SPROUT;
            break;
        case 20:
            p.growthPoints += randInt(0,5);
            p.growthPhase = GrowthPhase::FLOWERING;
            break;
        default: // Seed phase
            break;
    }
    p.growthPoints++;
}

void growPlants(std::vector<Plant> &plants) {
    for (auto& p : plants) {
        switch (p.type) {
            case PlantType::FLOWER:
                growFlower(p);
                break;
            case PlantType::TREE:
                growTree(p);
                break;
        }
        updateAge(p);
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
