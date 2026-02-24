#pragma once

#include <array>
#include <cassert>
#include <unordered_map>

#include "ECS/Types.hpp"

class IComponentArray {
    public:

    virtual ~IComponentArray() = default;
    virtual void entityDestroyed(Entity id) = 0;
};

template<typename T>
class ComponentArray : public IComponentArray {
    public:

    void insertData(Entity id, T component) {
        assert(idToIndex_.find(id) == idToIndex_.end()); // component already added

        size_t index = size_;
        idToIndex_[id] = index;
        indexToId_[index] = id;
        componentArray_[index] = component;
        size_++;
    }

    void removeData(Entity id) {
        assert(idToIndex_.find(id) != idToIndex_.end()); // component doesn't exist

        size_t removedIndex = idToIndex_[id];
        size_t lastIndex = --size_;
        componentArray_[removedIndex] = componentArray_[lastIndex];

        Entity lastId = indexToId_[lastIndex];
        idToIndex_[lastId] = removedIndex;
        indexToId_[removedIndex] = lastId;

        idToIndex_.erase(id);
        indexToId_.erase(lastIndex);
    }

    T& getData(Entity id) {
        assert(idToIndex_.find(id) != idToIndex_.end());

        return componentArray_[idToIndex_[id]];
    }

    void entityDestroyed(Entity id) override {
        if (idToIndex_.find(id) != idToIndex_.end()) {
            removeData(id);
        }
    }

    private:

    std::array<T, MAX_ENTITIES> componentArray_;

    std::unordered_map<Entity, size_t> idToIndex_;
    std::unordered_map<size_t, Entity> indexToId_;

    size_t size_;
};