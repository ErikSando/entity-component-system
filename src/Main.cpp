#include <iostream>
#include <memory>

#include "Components/RigidBody.hpp"
#include "Components/Transform.hpp"

#include "ECS/Scene.hpp"
#include "ECS/World.hpp"

#include "Systems/PhysicsSystem.hpp"

World world;

int main(/*int argc, char** argv*/) {
    world.init();

    world.registerComponent<RigidBody>();
    world.registerComponent<Transform>();

    std::shared_ptr<PhysicsSystem> physicsSystem = world.registerSystem<PhysicsSystem>();

    Signature physicsSignature;
    physicsSignature.set(world.getComponentType<RigidBody>());
    physicsSignature.set(world.getComponentType<Transform>());
    world.setSystemSignature<PhysicsSystem>(physicsSignature);

    physicsSystem->init();

    Scene scene1;
    Scene scene2;

    auto ebp1 = scene1.createBlueprint();
    ebp1->addComponent(Transform(Vector3f(0.0f, 0.5f, 0.0f), Vector3f(0.0f, 0.0f, 0.2f))).addComponent(RigidBody(Vector3f(0.1f, 0.3f, 0.2f), Vector3f(0.05f, 0.0f, 0.0f)));

    auto ebp2 = scene1.createBlueprint(
        Transform{
            Vector3f{0.5f, 0.5f, 0.5f},
            Vector3f{1.0f, 1.0f, 1.0f}
        }
    );

    auto ebp3 = scene2.createBlueprint();
    ebp3->addComponent(Transform(Vector3f(0.0f, 0.5f, 0.0f), Vector3f(0.0f, 0.0f, 0.2f))).addComponent(RigidBody(Vector3f(0.1f, 0.3f, 0.2f), Vector3f(0.05f, 0.0f, 0.0f)));

    auto ebp4 = scene2.createBlueprint(
        Transform{
            Vector3f{0.5f, 0.5f, 0.5f},
            Vector3f{1.0f, 1.0f, 1.0f}
        }
    );

    scene1.load(world);

    std::cout << ebp1->activeEntity << "\n";
    std::cout << ebp2->activeEntity << "\n";

    std::cout << world.hasComponent<Transform>(ebp1->activeEntity) << "\n";
    std::cout << world.hasComponent<RigidBody>(ebp1->activeEntity) << "\n";

    std::cout << "Position:      " << world.getComponent<Transform>(ebp1->activeEntity).position << "\n";
    std::cout << "Velocity:      " << world.getComponent<RigidBody>(ebp1->activeEntity).velocity << "\n";
    std::cout << "Acceleration:  " << world.getComponent<RigidBody>(ebp1->activeEntity).acceleration << "\n";
    std::cout << world.getComponent<Transform>(ebp2->activeEntity).position << "\n";

    for (int i = 0; i < 100; i++) {
        physicsSystem->update(1.0f / 60.0f);
    }

    std::cout << "Position:      " << world.getComponent<Transform>(ebp1->activeEntity).position << "\n";
    std::cout << "Velocity:      " << world.getComponent<RigidBody>(ebp1->activeEntity).velocity << "\n";
    std::cout << "Acceleration:  " << world.getComponent<RigidBody>(ebp1->activeEntity).acceleration << "\n";
    std::cout << world.getComponent<Transform>(ebp2->activeEntity).position << "\n";

    // scene1.unload(world);
    scene2.load(world);

    std::cout << "Position:      " << world.getComponent<Transform>(ebp3->activeEntity).position << "\n";
    std::cout << "Velocity:      " << world.getComponent<RigidBody>(ebp3->activeEntity).velocity << "\n";
    std::cout << "Acceleration:  " << world.getComponent<RigidBody>(ebp3->activeEntity).acceleration << "\n";
    std::cout << world.getComponent<Transform>(ebp4->activeEntity).position << "\n";

    for (int i = 0; i < 100; i++) {
        physicsSystem->update(1.0f / 60.0f);
    }

    std::cout << "Position:      " << world.getComponent<Transform>(ebp1->activeEntity).position << "\n";
    std::cout << "Velocity:      " << world.getComponent<RigidBody>(ebp1->activeEntity).velocity << "\n";
    std::cout << "Acceleration:  " << world.getComponent<RigidBody>(ebp1->activeEntity).acceleration << "\n";
    std::cout << world.getComponent<Transform>(ebp2->activeEntity).position << "\n";

    std::cout << "Position:      " << world.getComponent<Transform>(ebp3->activeEntity).position << "\n";
    std::cout << "Velocity:      " << world.getComponent<RigidBody>(ebp3->activeEntity).velocity << "\n";
    std::cout << "Acceleration:  " << world.getComponent<RigidBody>(ebp3->activeEntity).acceleration << "\n";
    std::cout << world.getComponent<Transform>(ebp4->activeEntity).position << "\n";

    return 0;
}