#pragma once

#include "game_data.h"
#include "types/player_controller.h"
#include "types/sprite.h"
#include "types/fish_body.h"
#include "iostream"

inline void handlePlayerInput(GameData &gd) {
    for (PlayerController &pc : gd.playerControllers) {
        unsigned int entityId = pc.entityId;
        unsigned int spriteIdx = gd.idToSpriteIdx[entityId];
        unsigned int fishBodyIdx = gd.idToFishBodyIdx[entityId];
        Sprite &s = gd.sprites[spriteIdx];
        FishBody &fb = gd.fishBodies[fishBodyIdx];

        if (IsKeyDown(pc.rightKey)) fb.worldCoords.x += 5.0f;
        if (IsKeyDown(pc.leftKey))  fb.worldCoords.x -= 5.0f;
        if (IsKeyDown(pc.upKey))    fb.worldCoords.y -= 5.0f;
        if (IsKeyDown(pc.downKey))  fb.worldCoords.y += 5.0f;
        s.worldCoords = fb.worldCoords;
    }
}

inline void addPlayerControllerToEntity(GameData& gd, unsigned int entityId) {
    PlayerController pc;
    pc.entityId = entityId;
    gd.playerControllers.push_back(pc);
}