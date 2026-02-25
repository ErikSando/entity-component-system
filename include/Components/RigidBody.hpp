#pragma once

#include "Math/Vector.hpp"

struct RigidBody {
    Vector3f velocity{};
    Vector3f acceleration{};

    RigidBody() = default;

    RigidBody(Vector3f _velocity, Vector3f _acceleration)
    : velocity(_velocity), acceleration(_acceleration) {}
};