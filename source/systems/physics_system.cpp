#include "physics_system.h"

constexpr float DRAG = 0.8f;

// v = d/t
// a = delta_v/t
// v = old_v + a*t
// How does mass fit in?
void applyForce(GameData &gd, unsigned int entityId, Vector2 force) {
    unsigned int pbIdx = gd.idToPhysicsBodyIdx[entityId];
    PhysicsBody &pb = gd.physicsBodies[pbIdx];

    // a = f/m
    pb.velocity.x += force.x/pb.mass;
    pb.velocity.y += force.y/pb.mass;
}

void velocityDisplace(PhysicsBody &pb, Vector2 &worldCoords) {
    worldCoords.x += pb.velocity.x;
    worldCoords.y += pb.velocity.y;
}

void applyDrag(PhysicsBody &pb) {
    pb.velocity.x *= DRAG;
    pb.velocity.y *= DRAG;
}

void simulatePhysics(GameData &gd) {
    for (PhysicsBody &pb : gd.physicsBodies) {
        // std::cout << "Physics info: {" << pb.velocity.x << ", " << pb.velocity.y << "}, " << pb.mass << "g\n";
        Vector2 &worldCoords = gd.idToWorldCoords[pb.entityId];

        velocityDisplace(pb, worldCoords);
        applyDrag(pb);
    }
}