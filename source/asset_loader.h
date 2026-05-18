#pragma once

#include "raylib.h"
#include "types/fish_body.h"
#include <vector>
#include <iostream>

#define ASSETS_DIR_PATH "/Users/andyk/Documents/GitHub/organic-growth/assets/"

inline std::vector<Color> loadPNG(const std::string& pngPath) {
    std::cout << "file path: -" << pngPath.c_str() << "-\n";
    Image img = LoadImage(pngPath.c_str());
    ImageFormat(&img, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
    auto* data = reinterpret_cast<unsigned char*>(img.data);

    std::vector<Color> pixels;
    for (int i = 0; i < img.width * img.height; i++) {
        pixels.push_back(Color{
            data[i * 4 + 0],
            data[i * 4 + 1],
            data[i * 4 + 2],
            data[i * 4 + 3]
        });
    }

    UnloadImage(img);
    return pixels;
}

inline std::vector<FishPart> loadFishPartsPNG(const std::string& pngPath) {
    std::vector<Color> pixels = loadPNG(pngPath);
    std::vector<FishPart> parts;
    for (Color &c : pixels) {
        c = RED;
        std::cout << (unsigned char)c.r << ", ";
        std::cout << c.g << ", ";
        std::cout << c.b << ", ";
        std::cout << c.a << ", \n";
    }

    return parts;
}

inline void loadFishAssets(GameData& gd, unsigned int entityId, const std::string& assetPrefix) {
    unsigned int spriteIdx = gd.idToSpriteIdx[entityId];
    unsigned int fishBodyIdx = gd.idToSpriteIdx[entityId];
    gd.sprites[spriteIdx].pixels = loadPNG(ASSETS_DIR_PATH + assetPrefix + "_Sprite.png");
    gd.fishBodies[fishBodyIdx].arr = loadFishPartsPNG(ASSETS_DIR_PATH + assetPrefix + "_Body.png");
}