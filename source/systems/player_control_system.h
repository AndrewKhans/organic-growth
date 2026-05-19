#pragma once

#include "game_data.h"
#include "types/player_controller.h"
// Todo: can we make this not include systems/physics_system?
#include "systems/physics_system.h"
#include "iostream"

inline void handlePlayerInput(GameData &gd) {
    for (PlayerController &pc : gd.playerControllers) {
        unsigned int id = pc.entityId;
        float mag = 5.0f;

        if (IsKeyDown(pc.rightKey)) applyAccel(gd, id, {mag, 0.0f});
        if (IsKeyDown(pc.leftKey))  applyAccel(gd, id, {-mag, 0.0f});
        if (IsKeyDown(pc.upKey))    applyAccel(gd, id, {0.0f, -mag});
        if (IsKeyDown(pc.downKey))  applyAccel(gd, id, {0.0f, mag});
    }
}

inline void addPlayerController(GameData& gd, unsigned int entityId) {
    PlayerController pc;
    pc.entityId = entityId;
    gd.playerControllers.push_back(pc);
}