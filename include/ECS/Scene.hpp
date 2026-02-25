#pragma once

#include <memory>
#include <utility>
#include <vector>

#include "Components/RigidBody.hpp"
#include "Components/Transform.hpp"

#include "ECS/ComponentLinker.hpp"
#include "ECS/Types.hpp"
#include "ECS/World.hpp"

struct EntityBlueprint {
    Entity activeEntity = NO_ENTITY;

    std::vector<std::unique_ptr<IComponentLinker>> componentLinkers;

    template<typename... TComponents>
    EntityBlueprint(TComponents&&... components) {
        addComponents(std::forward<TComponents>(components)...);
    }

    template<typename T>
    EntityBlueprint& addComponent(T&& component) {
        componentLinkers.push_back(
            std::make_unique<ComponentLinker<std::decay_t<T>>>(std::forward<T>(component))
        );
        return *this;
    }

    template<typename... TComponents>
    void addComponents(TComponents&&... components) {
        (componentLinkers.push_back(
            std::make_unique<ComponentLinker<std::decay_t<TComponents>>>(std::forward<TComponents>(components))
        ), ...);
    }
};

class Scene {
    public:

    template<typename... TComponents>
    std::shared_ptr<EntityBlueprint> createBlueprint(TComponents&&... components) {
        auto ebp = std::make_shared<EntityBlueprint>(std::forward<TComponents>(components)...);
        blueprints_.push_back(ebp);
        return ebp;
    }

    void load(World& world);
    void unload(World& world);

    private:

    bool loaded_ = false;

    std::vector<std::shared_ptr<EntityBlueprint>> blueprints_;
};