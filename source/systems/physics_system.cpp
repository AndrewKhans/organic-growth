#include "physics_system.h"
#include <cmath>

constexpr float DRAG = 0.8f;
constexpr float ROTATION_SPEED = 1.0f; // Deg/s

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

/* Nudge the entity's rotation to point towards its velocity */
void velocityRotate(PhysicsBody &pb, Transform2 &t) {
    if (abs(pb.velocity.x) + abs(pb.velocity.y) < 0.5) return;

    float velocityAngle = atan(pb.velocity.x/pb.velocity.y) * (180/PI);
    velocityAngle *= -1;
    if (pb.velocity.y >= 0) {
        velocityAngle += 180.0f;
    }

    std::cout << "Angle: " << velocityAngle << "\n";
    t.rot = velocityAngle;
}

void velocityDisplace(PhysicsBody &pb, Transform2 &t) {
    t.x += pb.velocity.x;
    t.y += pb.velocity.y;
}

void applyDrag(PhysicsBody &pb) {
    pb.velocity.x *= DRAG;
    pb.velocity.y *= DRAG;

    if (abs(pb.velocity.x) < 0.0001) pb.velocity.x = 0;
    if (abs(pb.velocity.y) < 0.0001) pb.velocity.y = 0;
}

void simulatePhysics(GameData &gd) {
    for (PhysicsBody &pb : gd.physicsBodies) {
        Transform2 &t = gd.idToTransform2[pb.entityId];

        velocityRotate(pb, t);
        velocityDisplace(pb, t);
        applyDrag(pb);
    }
}