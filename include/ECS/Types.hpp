#pragma once

#include <bitset>
#include <cstddef>
#include <cstdint>

using Entity = uint32_t;
constexpr size_t MAX_ENTITIES = 5000;
constexpr size_t NO_ENTITY = MAX_ENTITIES;

using ComponentType = uint8_t;
constexpr size_t MAX_COMPONENTS = 32;

using SystemType = uint8_t;
constexpr size_t MAX_SYSTEMS = 32;

using Signature = std::bitset<MAX_COMPONENTS>;