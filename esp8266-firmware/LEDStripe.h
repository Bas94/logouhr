#ifndef LED_STRIPE_H
#define LED_STRIPE_H

#include <stdint.h>
#include <Adafruit_NeoPixel.h>

class LEDStripe
{
public:
    LEDStripe( int pin, int numPixels );
    void setFullRGBColor( int r, int g, int b );
    void setFullHSVColor( int h, int s, int v );
    void setRGBColor( int i, int r, int g, int b );
    void setHSVColor( int i, int h, int s, int v );
    void setRGBLineColor( int start, int end, int r, int g, int b );
    void setHSVLineColor( int start, int end, int h, int s, int v );

private:
    void HSVtoRGB( uint16_t h, uint8_t s, uint8_t v, uint8_t& red, uint8_t& green, uint8_t& blue );

    int m_pin;
    int m_numPixels;
    Adafruit_NeoPixel m_stripe;
};

#endif
