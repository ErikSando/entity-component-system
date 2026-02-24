#pragma once

// purpose: provide entity IDs, keep track of which entities are active and which IDs are available

#include <array>
#include <cassert>
#include <queue>

#include "ECS/Types.hpp"

class EntityManager {
    public:

    EntityManager() {
        for (Entity id = 0; id < MAX_ENTITIES; id++) {
            availableEntityIDs_.push(id);
        }
    }

    Entity createEntity() {
        assert(entityCount_ < MAX_ENTITIES);

        Entity id = availableEntityIDs_.front();
        availableEntityIDs_.pop();
        entityCount_++;

        return id;
    }

    void destroyEntity(Entity id) {
        assert(id < MAX_ENTITIES);

        signatures_[id].reset();
        availableEntityIDs_.push(id);
        entityCount_--;
    }

    void setSignature(Entity id, Signature signature) {
        assert(id < MAX_ENTITIES);

        signatures_[id] = signature;
    }

    Signature getSignature(Entity id) {
        assert(id < MAX_ENTITIES);

        return signatures_[id];
    }

    private:

    std::queue<Entity> availableEntityIDs_{};
    std::array<Signature, MAX_ENTITIES> signatures_{};

    size_t entityCount_ = 0;
};