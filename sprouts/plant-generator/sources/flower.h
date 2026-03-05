#include "raylib.h"
#include <vector>

enum FlowerGrowthPhase {
    SEEDLING,
    LEAFY,
    FLOWER
};

enum PlantPart {
    AIR,
    SEED,
    STEM,
    LEAF,
    PETAL
};

class Flower {
    public:
        Flower(Vector2 loc);

        void grow();
        void draw();

    private:
        // Plant vars
        Vector2 loc; // The center of the bottom of the plant, in graphics-coords
        std::vector<std::vector<PlantPart>> plantArr; // Centered around loc. 0,0 is bottom left
        unsigned int age = 0;
        FlowerGrowthPhase growthPhase = SEEDLING;

        // Where the flower is currently growing from
        Vector2 growthPoint;

        // Traits assigned at birth
        Color petalColor;
        Color stemColor;
        int maxHeight;
};

