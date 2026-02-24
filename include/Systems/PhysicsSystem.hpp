#pragma once

#include "ECS/System.hpp"
#include "ECS/Types.hpp"

class PhysicsSystem : public System {
    public:

    void init();
    void update(float dt);
};