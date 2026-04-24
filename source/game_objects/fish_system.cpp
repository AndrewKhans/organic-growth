#include "fish_system.h"
#include <iostream>


Fish generateFish(Vector2 worldCoords) {
    Fish f;

    f.worldCoords = worldCoords;

    f.bodyArr.resize(f.arrWidth*f.arrHeight, FishPart::AIR);
    f.bodyArr[f.arrWidth*0 + (int)f.arrWidth/2] = FishPart::BODY;

    //
    int i = (int)f.arrWidth/2;

    f.bodyArr[i] = FishPart::BODY;
    f.bodyArr[i-1] = FishPart::BODY;
    f.bodyArr[i+1] = FishPart::BODY;

    return f;
}

void drawFish(std::vector<Fish> &fish) {

}
