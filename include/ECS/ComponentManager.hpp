#pragma once

#include <memory>
#include <unordered_map>

#include "ECS/ComponentArray.hpp"
#include "ECS/Types.hpp"

class ComponentManager {
    public:

    template<typename T>
    static ComponentType getComponentType() {
        static ComponentType componentType = nextComponentType_++;
        return componentType;
    }

    template<typename T>
    void registerComponent() {
        ComponentType type = getComponentType<T>();
        assert(componentArrays_[type] == nullptr); // component already registered
        componentArrays_[type] = std::make_shared<ComponentArray<T>>();
    }

    template<typename T>
    void addComponent(Entity id, T component) {
        getComponentArray<T>()->insertData(id, component);
    }

    template<typename T>
    void removeComponent(Entity id) {
        getComponentArray<T>()->removeData(id);
    }

    template<typename T>
    T& getComponent(Entity id) {
        return getComponentArray<T>()->getData(id);
    }

    void entityDestroyed(Entity id) {
        for (std::shared_ptr<IComponentArray>& array : componentArrays_) {
            if (array) {
                array->entityDestroyed(id);
            }
        }
    }

    private:

    inline static ComponentType nextComponentType_ = 0;

    std::array<std::shared_ptr<IComponentArray>, MAX_COMPONENTS> componentArrays_{};

    template<typename T>
    std::shared_ptr<ComponentArray<T>> getComponentArray() {
        ComponentType type = getComponentType<T>();
        std::shared_ptr<IComponentArray> array = componentArrays_[type];
        assert(array != nullptr); // component not registered
        return std::static_pointer_cast<ComponentArray<T>>(array);
    }
};