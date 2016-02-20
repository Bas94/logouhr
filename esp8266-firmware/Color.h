#ifndef __COLOR_H__
#define __COLOR_H__

#include <inttypes.h>

union Color{
    struct
    {
        uint8_t r;
        uint8_t g;
        uint8_t b;

    };
    uint32_t v:24;
};

namespace ColorOp
{
    void HSVtoRGB( uint16_t h, uint8_t s, uint8_t v, uint8_t& red, uint8_t& green, uint8_t& blue );
}

#endif // __COLOR_H__
