#pragma once

#include "ECS/Types.hpp"
#include "ECS/World.hpp"

class IComponentLinker {
    public:

    virtual ~IComponentLinker() = default;
    virtual void link(World& world, Entity entity) = 0;
};

template<typename T>
class ComponentLinker : public IComponentLinker {
    public:

    ComponentLinker(const T& component) : component_(component) {}
    ComponentLinker(T&& component) : component_(std::move(component)) {}

    void link(World& world, Entity entity) override {
        world.addComponent<T>(entity, component_);
    }

    private:

    T component_;
};