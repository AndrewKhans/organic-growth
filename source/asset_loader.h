#pragma once

#include "raylib.h"
#include "types/fish_body.h"
#include <vector>
#include <iostream>

// TODO: Make it so this isn't hardcoded
#define ASSETS_DIR_PATH "/Users/andyk/Documents/GitHub/organic-growth/assets/"

inline FishPart pixelToFishPart(const Color& c) {
    // TODO: Use a switch
    // TODO: Look up how to properly throw an error
    if (IS_BLANK(c)) {
        return FishPart::AIR;
    } else if (c.r == 255 && c.g == 0 && c.b == 0 && c.a == 255) {
        return FishPart::MOUTH;
    } else if (c.r == 255 && c.g == 163 && c.b == 0 && c.a == 255) {
        return FishPart::BODY;
    } else if (c.r == 32 && c.g == 255 && c.b == 0 && c.a == 255) {
        return FishPart::FIN;
    } else {
        std::cout << "Unrecognized pixel value for fish part conversion:\n";
        exit(1);
        return FishPart::BODY;
    }
}
inline Sprite loadSprite(unsigned int entityId, const std::string& pngPath) {
    Sprite s;
    s.entityId = entityId;

    Image img = LoadImage((ASSETS_DIR_PATH + pngPath).c_str());
    s.width = img.width;
    s.height = img.height;

    ImageFormat(&img, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
    auto* data = reinterpret_cast<unsigned char*>(img.data);

    s.pixels.resize(img.width * img.height, BLANK);
    for (int i = 0; i < img.width * img.height; i++) {
        // Add to pixels in reverse as ImageFormat starts from bottom left
        s.pixels[img.width * img.height - i - 1] = Color{
            data[i * 4 + 0],
            data[i * 4 + 1],
            data[i * 4 + 2],
            data[i * 4 + 3]
        };
    }

    UnloadImage(img);
    return s;
}

inline FishBody loadFishBody(unsigned int entityId, const std::string& pngPath) {
    FishBody fb;
    fb.entityId = entityId;

    Sprite bodySprite = loadSprite(entityId, pngPath);
    fb.width = bodySprite.width;
    fb.height = bodySprite.height;
    fb.arr.resize(fb.width*fb.height, FishPart::AIR);

    for (unsigned int i = 0; i < bodySprite.pixels.size(); i++)
        fb.arr[i] = pixelToFishPart(bodySprite.pixels[i]);

    return fb;
}

// inline void loadFishAssets(GameData& gd, unsigned int entityId, const std::string& assetPrefix) {
//     unsigned int spriteIdx = gd.idToSpriteIdx[entityId];
//     unsigned int fishBodyIdx = gd.idToFishBodyIdx[entityId];
//     gd.sprites[spriteIdx].pixels = loadPNG(ASSETS_DIR_PATH + assetPrefix + "_Sprite.png");
//     gd.fishBodies[fishBodyIdx].arr = loadFishPartsPNG(ASSETS_DIR_PATH + assetPrefix + "_Body.png");
// }