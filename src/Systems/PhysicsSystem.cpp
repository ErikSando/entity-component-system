#include "Components/RigidBody.hpp"
#include "Components/Transform.hpp"

#include "ECS/World.hpp"

#include "Systems/PhysicsSystem.hpp"

extern World world;

void PhysicsSystem::init() {

}

void PhysicsSystem::update(float dt) {
    for (Entity id : entities_) {
        RigidBody& rigidBody = world.getComponent<RigidBody>(id);
        Transform& transform = world.getComponent<Transform>(id);

        transform.position += rigidBody.velocity * dt;
        rigidBody.velocity += rigidBody.acceleration;
    }
}