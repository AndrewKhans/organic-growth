#pragma once

#include "raylib.h"
#include "types/fish_body.h"
#include <vector>
#include <iostream>

#define ASSETS_DIR_PATH "/Users/andyk/Documents/GitHub/organic-growth/assets/"

inline std::vector<Color> loadPNG(const std::string& pngPath) {
    Image img = LoadImage(pngPath.c_str());
    ImageFormat(&img, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
    auto* data = reinterpret_cast<unsigned char*>(img.data);

    std::vector<Color> pixels(img.width * img.height);
    for (int i = 0; i < img.width * img.height; i++) {
        // Add to pixels in reverse as ImageFormat starts from bottom left
        pixels[img.width * img.height - i - 1] = Color{
            data[i * 4 + 0],
            data[i * 4 + 1],
            data[i * 4 + 2],
            data[i * 4 + 3]
        };
    }

    UnloadImage(img);
    // for (auto &p : pixels) p = BROWN;
    return pixels;
}

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
        std::cout << "Unrecognized fish part\n";
        exit(1);
        return FishPart::BODY;
    }
}

inline std::vector<FishPart> loadFishPartsPNG(const std::string& pngPath) {
    std::vector<Color> pixels = loadPNG(pngPath);
    std::vector<FishPart> parts(pixels.size());

    for (unsigned int i = 0; i < pixels.size(); i++)
        parts[i] = pixelToFishPart(pixels[i]);

    return parts;
}

inline void loadFishAssets(GameData& gd, unsigned int entityId, const std::string& assetPrefix) {
    unsigned int spriteIdx = gd.idToSpriteIdx[entityId];
    unsigned int fishBodyIdx = gd.idToFishBodyIdx[entityId];
    gd.sprites[spriteIdx].pixels = loadPNG(ASSETS_DIR_PATH + assetPrefix + "_Sprite.png");
    gd.fishBodies[fishBodyIdx].arr = loadFishPartsPNG(ASSETS_DIR_PATH + assetPrefix + "_Body.png");
}