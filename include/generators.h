#pragma once
#include <cstdlib>
#include "rational.h"


class estimate_pi
{
    const float epsilon;
    uint inside_count;
    uint total_count;
    float delta;

    static uint count_in_quadrant(const uint total);

public:

    estimate_pi(const float epsilon_) : epsilon(abs(epsilon_)), inside_count(1), total_count(1), delta(1.0) {}

    bool finished()
    {
        return abs(delta) < epsilon;
    }

    rational next();

};