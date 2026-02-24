#pragma once

#include <set>

#include "ECS/Types.hpp"

class System {
    public:

    std::set<Entity> entities_;
};