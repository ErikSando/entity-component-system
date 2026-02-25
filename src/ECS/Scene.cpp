#include <iostream>

#include "ECS/Scene.hpp"
#include "ECS/World.hpp"

void Scene::load(World& world) {
    if (loaded_) return;

    for (auto ebp : blueprints_) {
        Entity newEntity = world.createEntity();
        ebp->activeEntity = newEntity;

        for (std::unique_ptr<IComponentLinker>& componentLinker : ebp->componentLinkers) {
            componentLinker->link(world, newEntity);
        }
    }

    loaded_ = true;
}

void Scene::unload(World& world) {
    if (!loaded_) return;

    for (auto ebp : blueprints_) {
        Entity entity = ebp->activeEntity;
        if (entity == NO_ENTITY) continue;

        world.destroyEntity(entity);
        ebp->activeEntity = NO_ENTITY;
    }

    loaded_ = false;
}