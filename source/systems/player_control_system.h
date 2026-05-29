#pragma once

#include "game_data.h"
#include "types/player_controller.h"
// Todo: can we make this not include systems/physics_system?
#include "systems/physics_system.h"
#include "iostream"

inline void handlePlayerInput(GameData &gd) {
    for (PlayerController &pc : gd.playerControllers) {
        unsigned int id = pc.entityId;
        PhysicsBody &pb = gd.physicsBodies[gd.idToPhysicsBodyIdx[id]];
        FishBody &fb = gd.fishBodies[gd.idToFishBodyIdx[id]];

        Vector2 force = {0.0f, 0.0f};
        if (IsKeyDown(pc.rightKey)) force.x += 1;
        if (IsKeyDown(pc.leftKey))  force.x -= 1;
        if (IsKeyDown(pc.upKey))    force.y -= 1;
        if (IsKeyDown(pc.downKey))  force.y += 1;

        // Normalize so that moving diagonal is the same speed as cardinal
        if (force.x != 0 && force.y != 0) {
            force.x *= 0.7071f;
            force.y *= 0.7071f;
        }

        // Todo: Add operator override for Vector2 * Scalar
        force.x *= fb.swimForce;
        force.y *= fb.swimForce;

        applyForce(pb, force);
    }
}

inline void addPlayerController(GameData& gd, unsigned int entityId) {
    // todo: ensure the target has a physics body
    PlayerController pc;
    pc.entityId = entityId;
    gd.playerControllers.push_back(pc);
    gd.idToPlayerControllerIdx[entityId] = gd.playerControllers.size()-1;
}