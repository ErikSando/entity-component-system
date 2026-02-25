#pragma once

#include <iostream>
#include <memory>

#include "ECS/ComponentManager.hpp"
#include "ECS/EntityManager.hpp"
#include "ECS/SystemManager.hpp"

class World {
    public:

    void init() {
        componentManager_ = std::make_unique<ComponentManager>();
        entityManager_ = std::make_unique<EntityManager>();
        systemManager_ = std::make_unique<SystemManager>();
    }

    Entity createEntity() {
        return entityManager_->createEntity();
    }

    void destroyEntity(Entity id) {
        entityManager_->destroyEntity(id);
        componentManager_->entityDestroyed(id);
        systemManager_->entityDestroyed(id);
    }

    template<typename T>
    void registerComponent() {
        componentManager_->registerComponent<T>();
    }

    template<typename T>
    void addComponent(Entity id, T component) {
        componentManager_->addComponent<T>(id, component);
        Signature signature = entityManager_->getSignature(id);
        signature.set(componentManager_->getComponentType<T>(), true);
        entityManager_->setSignature(id, signature);
        systemManager_->entitySignatureChanged(id, signature);
    }

    template<typename T>
    void removeComponent(Entity id) {
        componentManager_->removeComponent<T>(id);
        Signature signature = entityManager_->getSignature(id);
        signature.set(componentManager_->getComponentType<T>(), false);
        entityManager_->setSignature(id, signature);
        systemManager_->entitySignatureChanged(id, signature);
    }

    template<typename T>
    bool hasComponent(Entity id) {
        Signature signature = entityManager_->getSignature(id);
        return signature.test(componentManager_->getComponentType<T>());
    }

    template<typename T>
    T& getComponent(Entity id) {
        return componentManager_->getComponent<T>(id);
    }

    template<typename T>
    ComponentType getComponentType() {
        return componentManager_->getComponentType<T>();
    }

    template<typename T>
    std::shared_ptr<T> registerSystem() {
        return systemManager_->registerSystem<T>();
    }

    template<typename T>
    void setSystemSignature(Signature signature) {
        systemManager_->setSignature<T>(signature);
    }

    private:

    std::unique_ptr<ComponentManager> componentManager_;
    std::unique_ptr<EntityManager> entityManager_;
    std::unique_ptr<SystemManager> systemManager_;
};