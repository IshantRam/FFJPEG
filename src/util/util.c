#include "util/util.h"

// Wrap
u8 wrap(s64 value)
{
    if (value > 255)
    {
        return 255;
    }
    else if (value < 0)
    {
        return 0;
    };
    return value;
};