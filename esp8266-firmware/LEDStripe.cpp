#include "LEDStripe.h"

#include <EEPROM.h>

LEDStripe::LEDStripe(int pin, int numPixels , int saveLoadOffset)
    : m_pin( pin )
    , m_numPixels( numPixels )
    , m_stripe( m_numPixels, m_pin, NEO_GRB + NEO_KHZ800 )
    , m_saveLoadOffset( saveLoadOffset )
{
    readStateFromEEPROM();
    m_stripe.begin();
    setFullRGBColor( 0, 0, 0 );
    refresh();
}

void LEDStripe::setFullRGBColor( int r, int g, int b )
{
    uint32_t col = m_stripe.Color( r, g, b );
    for( int i = 0; i < m_numPixels; ++i )
    {
        m_stripe.setPixelColor( i, col );
    }
    m_stripe.show();
    saveStateToEEPROM();
}

void LEDStripe::setFullHSVColor( int h, int s, int v )
{
    uint8_t r, g, b;
    HSVtoRGB( h, s, v, r, g, b );
    setFullRGBColor( r, g, b );
}

void LEDStripe::setRGBColor( int i, int r, int g, int b )
{
    m_stripe.setPixelColor( i, r, g, b );
    m_stripe.show();
    saveStateToEEPROM();
}

void LEDStripe::setHSVColor( int i, int h, int s, int v )
{
    uint8_t r, g, b;
    HSVtoRGB( h, s, v, r, g, b );
    setRGBColor( i, r, g, b );
}

void LEDStripe::setRGBLineColor( int start, int end, int r, int g, int b )
{
    int minI = start > end ? end : start;
    int maxI = start < end ? end : start;
    uint32_t col = m_stripe.Color( r, g, b );
    for( int i = minI; i < maxI; ++i )
    {
        m_stripe.setPixelColor( i, col );
    }
    m_stripe.show();
    saveStateToEEPROM();
}

void LEDStripe::setHSVLineColor( int start, int end, int h, int s, int v )
{
    uint8_t r, g, b;
    HSVtoRGB( h, s, v, r, g, b );
    setRGBLineColor( start, end, r, g, b );
}

void LEDStripe::addRGBColor( int i, int r, int g, int b )
{
    uint32_t col = m_stripe.Color( r, g, b );
    m_stripe.setPixelColor( i, col );
}

void LEDStripe::addHSVColor( int i, int h, int s, int v )
{
    uint8_t r, g, b;
    HSVtoRGB( h, s, v, r, g, b );
    addRGBColor( i , r, g, b );
}

void LEDStripe::addFullRGBColor( int r, int g, int b )
{
    uint32_t col = m_stripe.Color( r, g, b );
    for( int i = 0; i < m_numPixels; ++i )
        m_stripe.setPixelColor( i, col );
}

void LEDStripe::addFullHSVColor( int h, int s, int v )
{
    uint8_t r, g, b;
    HSVtoRGB( h, s, v, r, g, b );
    addFullRGBColor( r, g, b );
}

void LEDStripe::refresh()
{
    m_stripe.show();
    saveStateToEEPROM();
}

int LEDStripe::getNumberOfPixels()
{
    return m_numPixels;
}

void LEDStripe::saveStateToEEPROM()
{
    //for( int i = 0; i < m_numPixels; ++i )
    //{
    //    uint32_t color = m_stripe.getPixelColor( i );
    //    EEPROM.write( m_saveLoadOffset + i * 3 + 0, ( color | 0x0000FF ) );
    //    EEPROM.write( m_saveLoadOffset + i * 3 + 1, ( color | 0x00FF00 ) >> 8 );
    //    EEPROM.write( m_saveLoadOffset + i * 3 + 2, ( color | 0xFF0000 ) >> 16 );
    //}
}

void LEDStripe::readStateFromEEPROM()
{
    //for( int i = 0; i < m_numPixels; ++i )
    //{
    //    uint32_t color = 0;
    //    color += EEPROM.read( m_saveLoadOffset + i * 3 + 0 );
    //    color += EEPROM.read( m_saveLoadOffset + i * 3 + 1 ) << 8;
    //    color += EEPROM.read( m_saveLoadOffset + i * 3 + 2 ) << 16;
    //    m_stripe.setPixelColor( i, color );
    //}
    //m_stripe.show();
}

void LEDStripe::HSVtoRGB( uint16_t h, uint8_t s, uint8_t v, uint8_t& red, uint8_t& green, uint8_t& blue )
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
        case(6): red = v; green = t; blue = p; break;
        case(1): red = q; green = v; blue = p; break;
        case(2): red = p; green = v; blue = t; break;
        case(3): red = p; green = q; blue = v; break;
        case(4): red = t; green = p; blue = v; break;
        case(5): red = v; green = p; blue = q; break;
    default:
        blue = 0; green = 0; red = 0; break;
    }
}
