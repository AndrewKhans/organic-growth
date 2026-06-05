#include "physics_system.h"
#include <cmath>

constexpr float DRAG = 0.87f;
constexpr float ROTATION_SPEED = 1.0f; // Deg/s

// How to properly add multiple forces? If we already have f1, and we want to add f2, how should that work?
void applyForce(PhysicsBody &pb, Vector2 force) {
    // a = f/m
    pb.velocity.x += force.x/pb.mass;
    pb.velocity.y += force.y/pb.mass;
    std::cout << "mass " << pb.mass << "\n";
    std::cout << "velocity " << pb.velocity.x << ", " << pb.velocity.y << "\n";
}

/* Nudge the entity's rotation to point towards its velocity */
void velocityRotate(PhysicsBody &pb, Transform2 &t) {
    if (abs(pb.velocity.x) + abs(pb.velocity.y) < 0.5) return;

    float velocityAngle = atan(pb.velocity.x/pb.velocity.y) * (180/PI);
    velocityAngle *= -1;
    if (pb.velocity.y >= 0) {
        velocityAngle += 180.0f;
    }

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