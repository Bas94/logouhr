#ifndef __COLOR_H__
#define __COLOR_H__

#include <inttypes.h>

union ColorHSV;

union Color{
    struct
    {
        uint8_t r;
        uint8_t g;
        uint8_t b;

    };
    uint32_t data:24;

    Color();
    Color( uint8_t red, uint8_t green, uint8_t blue );
    Color( Color const & color );
    Color& operator=( ColorHSV const & rhs );
    Color& operator=( Color const & rhs );
};

union ColorHSV{
    struct
    {
        uint16_t h;
        uint8_t s;
        uint8_t v;
    };
    uint32_t data:32;

    ColorHSV();
    ColorHSV( uint16_t hue, uint8_t saturation, uint8_t value );
    ColorHSV( ColorHSV const & color );
    ColorHSV& operator=( Color const & rhs );
    ColorHSV& operator=( ColorHSV const & rhs );
};

namespace ColorOp
{
    void HSVtoRGB( uint16_t h, uint8_t s, uint8_t v, uint8_t& red, uint8_t& green, uint8_t& blue );
    Color HSVtoRGB( ColorHSV const & col );
    void RGBtoHSV( uint8_t red, uint8_t green, uint8_t blue, uint16_t& h, uint8_t& s, uint8_t& v );
    ColorHSV RGBtoHSV( Color const & col );
}

#endif // __COLOR_H__
