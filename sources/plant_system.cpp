#include "plant_system.h"
#include <iostream>
#include <vector>
#include <random>

int randInt(int min, int max) {
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(rng);
}

Plant generateFlower(CoordPair seedLocation) {
    Plant p;

    p.type = PlantType::FLOWER;
    p.loc = seedLocation;
    p.growthPoint = seedLocation;

    p.plantArr.resize(p.arrWidth*p.arrHeight, PlantPart::AIR);
    p.plantArr[p.arrWidth*0 + (int)p.arrWidth/2] = PlantPart::SEED;
    p.growthPoint = {(int)p.arrWidth/2, 0};

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

Plant generateTree(CoordPair seedLocation) {
    Plant p;

    p.type = PlantType::TREE;
    p.loc = seedLocation;
    p.growthPoint = seedLocation;

    p.plantArr.resize(p.arrWidth*p.arrHeight, PlantPart::AIR);
    p.plantArr[p.arrWidth*0 + (int)p.arrWidth/2] = PlantPart::SEED;
    p.growthPoint = {(int)p.arrWidth/2, 0};

    // Assign random birth traits
    p.stemColor = BROWN;

    p.barkColor = BROWN;

    return p;
}

void growSeedling(Plant& p) {

}

void growSprout(Plant& p) {
    p.plantArr[p.growthPoint.x + p.growthPoint.y*p.arrWidth] = PlantPart::STEM;
    p.growthPoint.y += 1;

    // Stem shift
    if (p.growthPoint.y > 1 &&
        p.plantArr[p.growthPoint.x + (p.growthPoint.y-1)*p.arrWidth] != PlantPart::AIR &&
        p.plantArr[p.growthPoint.x + (p.growthPoint.y-2)*p.arrWidth] != PlantPart::AIR &&
        randInt(0,6) == 0) {

        int offset = randInt(0,1) == 0 ? 1 : -1;
        p.growthPoint.x += offset;
    }
}

void growBarky(Plant& p) {

}

void growFlowering(Plant& p) {
    p.plantArr[p.growthPoint.x + p.growthPoint.y*p.arrWidth] = PlantPart::PETAL;

    // Need to apply a formula that fills in a circle shape
    // x=rcos(theta) y=rsin(theta), theta increases each step and r increases each time
    // we loop back around
}


void growFlower(Plant& p) {
    switch (p.growthPhase) {
        case GrowthPhase::SEED:
            if (p.growthPoints == 5) {
                p.growthPoints = randInt(0,5);
                p.growthPhase = GrowthPhase::SPROUT;
            }
            break;
        case GrowthPhase::SPROUT:
            growSprout(p);
            if (p.growthPoints == 20) {
                p.growthPoints = randInt(0,5);
                p.growthPhase = GrowthPhase::FLOWERING;
            }
            break;
        case GrowthPhase::FLOWERING:
            growFlowering(p);
            p.growthPoints = 0;
            p.growthPhase = GrowthPhase::DORMANT;
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
            if (p.growthPoints == 5) {
                p.growthPoints = randInt(0,5);
                p.growthPhase = GrowthPhase::SPROUT;
            }
            break;
        case GrowthPhase::SPROUT:
            growSprout(p);
            if (p.growthPoints == 20) {
                p.growthPoints = randInt(0,5);
                p.growthPhase = GrowthPhase::BARKY;
            }
            break;
        case GrowthPhase::BARKY:
            growBarky(p);
            if (p.growthPoints == 20) {
                p.growthPoints = 0;
                p.growthPhase = GrowthPhase::DORMANT;
            }
            break;
        case GrowthPhase::DORMANT:
            break;
        default:
            throw std::runtime_error("Unexpected growth phase");
    }
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
        p.growthPoints++;
    }
}

void drawPlants(std::vector<Plant> &plants) {
    Color c;
    PlantPart part;

    for (const auto& p : plants) {
        for (unsigned int arr_y = 0; arr_y < p.arrHeight; arr_y++) {
            for (unsigned int arr_x = 0; arr_x < p.arrWidth; arr_x++) {
                part = p.plantArr[arr_x + arr_y*p.arrWidth];
                if (part == PlantPart::AIR) continue;

                switch (part) {
                    case PlantPart::AIR: break;
                    case PlantPart::SEED:
                        c = BROWN;
                        break;
                    case PlantPart::STEM:
                        c = p.stemColor;
                        break;
                    case PlantPart::LEAF:
                    case PlantPart::LEAFBASE:
                        c = p.stemColor;
                        break;
                    case PlantPart::PETALBASE:
                        c = BROWN;
                        break;
                    case PlantPart::PETAL:
                        c = p.petalColor;
                        break;
                }

                int x = p.loc.x + (arr_x-(int)p.arrWidth/2)*PIXEL_SIZE;
                int y = p.loc.y - arr_y*PIXEL_SIZE;
                DrawRectangle(x, y, PIXEL_SIZE, PIXEL_SIZE, c);
            }
        }
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
