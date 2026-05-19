#include "physics_system.h"

constexpr float DRAG = 0.2f;

// v = d/t
// a = delta_v/t
// v = old_v + a*t
// How does mass fit in?
void applyAccel(GameData &gd, unsigned int entityId, Vector2 accel) {
    unsigned int pbIdx = gd.idToPhysicsBodyIdx[entityId];
    PhysicsBody &pb = gd.physicsBodies[pbIdx];

    // Todo: Can I override += for Vector2?
    pb.velocity.x += accel.x;
    pb.velocity.y += accel.y;
}

void velocityDisplace(PhysicsBody &pb, Vector2 worldCoords) {
    worldCoords.x += pb.velocity.x;
    worldCoords.y += pb.velocity.y;
}

void applyDrag(PhysicsBody &pb) {
    pb.velocity.x *= DRAG;
    pb.velocity.y *= DRAG;
}

void simulatePhysics(GameData &gd) {
    for (PhysicsBody &pb : gd.physicsBodies) {
        Vector2 &worldCoords = gd.idToWorldCoords[pb.entityId];

        velocityDisplace(pb, worldCoords);
        applyDrag(pb);
    }
}