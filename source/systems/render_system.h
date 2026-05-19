#pragma once

#include "raylib.h"
#include "types/sprite.h"
#include <vector>

constexpr unsigned int PIXEL_SIZE = 20;
// constexpr unsigned int PIXEL_SIZE = 12;

// TODO: Do I need to make this static? I want the function to be hidden from people outside this file,
// but if I just don't include it in the .h and only have it in the .cpp, that might do that
static void drawSprite(const Sprite& s);
void drawWorld(const std::vector<Sprite>& sprites);
