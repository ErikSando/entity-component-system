#pragma once

#include <array>
#include <memory>

#include "ECS/System.hpp"
#include "ECS/Types.hpp"

class SystemManager {
    public:

    template<typename T>
    static SystemType getSystemType() {
        static SystemType systemType = nextSystemType_++;
        return systemType;
    }

    template<typename T>
    std::shared_ptr<T> registerSystem() {
        SystemType type = getSystemType<T>();

        assert(systems_[type] == nullptr); // system already registered

        std::shared_ptr<T> system = std::make_shared<T>();
        systems_[type] = system;

        return system;
    }

    template<typename T>
    void setSignature(Signature signature) {
        SystemType type = getSystemType<T>();

        assert(systems_[type] != nullptr); // system not registered

        signatures_[type] = signature;
    }

    void entityDestroyed(Entity id) {
        for (std::shared_ptr<System>& system : systems_) {
            if (system) {
                system->entities_.erase(id);
            }
        }
    }

    void entitySignatureChanged(Entity id, Signature entitySignature) {
        for (SystemType type = 0; type < MAX_SYSTEMS; type++) {
            std::shared_ptr<System> system = systems_[type];
            if (!system) continue;

            const Signature& systemSignature = signatures_[type];

            if ((entitySignature & systemSignature) == systemSignature) {
                system->entities_.insert(id);
            }
            else {
                system->entities_.erase(id);
            }
        }
    }

    private:

    inline static SystemType nextSystemType_ = 0;

    std::array<std::shared_ptr<System>, MAX_SYSTEMS> systems_{};
    std::array<Signature, MAX_SYSTEMS> signatures_{};
};