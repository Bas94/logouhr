#ifndef LED_STRIPE_H
#define LED_STRIPE_H

#include <stdint.h>
#include <Adafruit_NeoPixel.h>

class LEDStripe
{
public:
    LEDStripe( Adafruit_NeoPixel& parent, int numPixels );

    LEDStripe( int pin, int numPixels );
    virtual void setFullRGBColor( int r, int g, int b );
    void setFullHSVColor( int h, int s, int v );
    virtual void setRGBColor( int i, int r, int g, int b );
    void setHSVColor( int i, int h, int s, int v );
    virtual void setRGBLineColor( int start, int end, int r, int g, int b );
    void setHSVLineColor( int start, int end, int h, int s, int v );

    virtual void addRGBColor( int i, int r, int g, int b );
    void addHSVColor( int i, int h, int s, int v );

    virtual void addFullRGBColor( int r, int g, int b );
    void addFullHSVColor( int h, int s, int v );

    virtual void refresh();

    int getNumberOfPixels();

protected:
    void HSVtoRGB( uint16_t h, uint8_t s, uint8_t v, uint8_t& red, uint8_t& green, uint8_t& blue );

    int m_numPixels;
    Adafruit_NeoPixel & m_stripe;
    int m_saveLoadOffset;
};

class LEDStripeSnippet : public LEDStripe
{
public:
    LEDStripeSnippet( Adafruit_NeoPixel& parent, int begin, int numPixels );
    void setFullRGBColor( int r, int g, int b );
    void setRGBColor( int i, int r, int g, int b );
    void setRGBLineColor( int start, int end, int r, int g, int b );

    void addRGBColor( int i, int r, int g, int b );

    void addFullRGBColor( int r, int g, int b );

protected:
    int m_addressOffset;
};


#endif
