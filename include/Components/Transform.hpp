#pragma once

#include "Math/Vector.hpp"

struct Transform {
    Vector3f position{};
    Vector3f size{};

    Transform() = default;

    Transform(Vector3f _position, Vector3f _size)
    : position(_position), size(_size) {}
};