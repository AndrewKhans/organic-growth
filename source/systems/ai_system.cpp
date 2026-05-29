#include "ai_system.h"


void addAiBrain(GameData& gd, unsigned int entityId) {
    // Ensure the target has a physicsBody
    AiBrain ai;
    ai.entityId = entityId;
    gd.aiBrains.push_back(ai);
    gd.idToAiBrainIdx[entityId] = gd.aiBrains.size()-1;
}

void randomFishMovement(PhysicsBody& pb, const FishBody& fb) {
    unsigned char direction = randInt(0,8);

    Vector2 force = {0.0f, 0.0f};
    switch (direction) {
        case 0:
            force = {0,1};
            break;
        case 1:
            force = {1,0};
            break;
        case 2:
            force = {-1,0};
            break;
        case 3:
            force = {0,-1};
            break;
        case 4:
            force = {0.7071f,0.7071f};
            break;
        case 5:
            force = {-0.7071f,0.7071f};
            break;
        case 6:
            force = {0.7071f,-0.7071f};
            break;
        case 7:
            force = {-0.7071f,-0.7071f};
            break;
    }

    force.x *= (fb.swimForce * 5);
    force.y *= (fb.swimForce * 5);

    applyForce(pb, force);
}

void aiDecisions(GameData &gd, unsigned int tickCount) {
    for (AiBrain &ai : gd.aiBrains) {
        unsigned int id = ai.entityId;
        const FishBody& fb = gd.fishBodies[gd.idToFishBodyIdx[id]];
        PhysicsBody &pb = gd.physicsBodies[gd.idToPhysicsBodyIdx[id]];

        if (tickCount - ai.lastMovementTick > 120) {
            randomFishMovement(pb, fb);
            ai.lastMovementTick = tickCount;
        }
    }
}