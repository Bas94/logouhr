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

    Color HSVtoRGB( ColorHSV const & col )
    {
        Color c;
        HSVtoRGB( col.h, col.s, col.v, c.r, c.g, c.b );
        return c;
    }

    void RGBtoHSV(uint8_t red, uint8_t green, uint8_t blue, uint16_t &h, uint8_t &s, uint8_t &v)
    {
        uint8_t maxVal = max( red, max( green, blue ) );
        uint8_t minVal = min( red, min( green, blue ) );
        if( maxVal == minVal )
            h = 0;
        else if( maxVal == red )
            h = 60 * ( 0 + ( green - blue  ) / ( maxVal - minVal ) );
        else if( maxVal == green )
            h = 60 * ( 2 + ( blue  - red   ) / ( maxVal - minVal ) );
        else if( maxVal == blue )
            h = 60 * ( 4 + ( red   - green ) / ( maxVal - minVal ) );

        if( h < 0 )
            h += 360;

        if( maxVal == 0 )
            s = 0;
        else
            s = ( maxVal - minVal ) / maxVal;

        v = maxVal;
    }

    ColorHSV RGBtoHSV( Color const & col )
    {
        ColorHSV c;
        RGBtoHSV( col.r, col.g, col.b, c.h, c.s, c.v );
        return c;
    }

} // namespace ColorOp

Color::Color()
    : data( 0 )
{
}

Color::Color( uint8_t red, uint8_t green, uint8_t blue )
    : r( red )
    , g( green )
    , b( blue )
{
}

Color::Color( const Color &color )
    : r( color.r )
    , g( color.g )
    , b( color.b )
{
}

Color& Color::operator=( ColorHSV const & rhs )
{
    *this = ColorOp::HSVtoRGB( rhs );
    return *this;
}

Color& Color::operator=( Color const & rhs )
{
    this->r = rhs.r;
    this->g = rhs.g;
    this->b = rhs.b;
    return *this;
}

ColorHSV::ColorHSV()
    : data( 0 )
{
}

ColorHSV::ColorHSV( uint16_t hue, uint8_t saturation, uint8_t value )
    : h( hue )
    , s( saturation )
    , v( value )
{
}

ColorHSV::ColorHSV( const ColorHSV &color )
    : h( color.h )
    , s( color.s )
    , v( color.v )
{
}

ColorHSV& ColorHSV::operator=( Color const & rhs )
{
    *this = ColorOp::RGBtoHSV( rhs );
    return *this;
}

ColorHSV& ColorHSV::operator=( const ColorHSV &rhs )
{
    this->h = rhs.h;
    this->s = rhs.s;
    this->v = rhs.v;
    return *this;
}
