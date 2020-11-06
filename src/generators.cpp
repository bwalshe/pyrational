#include <limits>
#include "generators.h"
#include "rational.h"


static const uint BATCH_SIZE = 5;


rational estimate_pi::next()
{
    rational old_val(inside_count, total_count);
    inside_count += count_in_quadrant(BATCH_SIZE);
    total_count += BATCH_SIZE;
    rational new_val(inside_count, total_count);
    delta = static_cast<float>(old_val - new_val);
    return  new_val * 4;
}


uint estimate_pi::count_in_quadrant(const uint total)
{
    uint inside = 0;
    for(uint i = 0; i < total; ++i) 
    {
        float x = static_cast <float> (rand()) / static_cast<float>(RAND_MAX);
        float y = static_cast <float> (rand()) / static_cast<float>(RAND_MAX);
        if(x * x + y * y < 1.0)
            inside++;
    }

    return inside;
}