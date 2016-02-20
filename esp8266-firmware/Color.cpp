#include "Color.h"

namespace ColorOp
{
    void HSVtoRGB( uint16_t h, uint8_t s, uint8_t v, uint8_t& red, uint8_t& green, uint8_t& blue )
    {
        h=h%360;
        uint8_t hi = h / 60;
        uint8_t f = h % 60;
        int p = (static_cast<uint16_t>(v)*(255-static_cast<uint16_t>(s)))/255;
        int q = (static_cast<uint16_t>(v)*(255-static_cast<uint16_t>(s)*f/60))/255;
        int t = (static_cast<uint16_t>(v)*(255-static_cast<uint16_t>(s)*(60-f)/60))/255;
        switch(hi)
        {
            case(0):
            case(6): blue = v; green = t; red = p; break;
            case(1): blue = q; green = v; red = p; break;
            case(2): blue = p; green = v; red = t; break;
            case(3): blue = p; green = q; red = v; break;
            case(4): blue = t; green = p; red = v; break;
            case(5): blue = v; green = p; red = q; break;
        default:
            blue = 0; green = 0; red = 0; break;
        }
    }

} // namespace ColorOp
