#include <iostream>
#include <memory>

#include "Components/RigidBody.hpp"
#include "Components/Transform.hpp"

#include "ECS/World.hpp"

#include "Systems/PhysicsSystem.hpp"

World world;

int main(/*int argc, char** argv*/) {
    world.init();

    std::shared_ptr<PhysicsSystem> physicsSystem = world.registerSystem<PhysicsSystem>();

    world.registerComponent<RigidBody>();
    world.registerComponent<Transform>();

    Signature physicsSignature;
    physicsSignature.set(world.getComponentType<RigidBody>());
    physicsSignature.set(world.getComponentType<Transform>());
    world.setSystemSignature<PhysicsSystem>(physicsSignature);

    physicsSystem->init();

    RigidBody rb0;
    Transform t0;

    rb0.velocity = { 1.0f, 0.0f, 0.5f };

    Entity e0 = world.createEntity();
    world.addComponent<RigidBody>(e0, rb0); // dont need the <RigidBody> but I like explicit code
    world.addComponent<Transform>(e0, t0);

    Transform t1;

    Entity e1 = world.createEntity();
    world.addComponent<Transform>(e1, t1);

    RigidBody& rb0r = world.getComponent<RigidBody>(e0);
    Transform& t0r = world.getComponent<Transform>(e0);
    Transform& t1r = world.getComponent<Transform>(e1);

    std::cout << rb0r.velocity << "\n";
    std::cout << t0r.position << "\n";
    std::cout << t1r.position << "\n";

    for (int i = 0; i < 100; i++) {
        physicsSystem->update(1.0f / 60.0f);
    }

    std::cout << rb0r.velocity << "\n";
    std::cout << t0r.position << "\n";
    std::cout << t1r.position << "\n";

    return 0;
}