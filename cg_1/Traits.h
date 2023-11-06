#pragma once
#include <cstdint>
#include <limits>

struct ColorTypeTrait8_t
{
    using codingType = std::uint8_t;
    static const int max = std::numeric_limits<codingType>::max();
    static const int bound = 256;
};