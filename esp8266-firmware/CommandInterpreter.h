#ifndef __COMMAND_INTERPRETER_H__
#define __COMMAND_INTERPRETER_H__

#include "LEDStripe.h"
#include "Color.h"

class String;

/*!
 * \brief The CommandInterpreter class
 *
 * Protocol:
 * mode generic/clock
 *
 * clock HH MM SS\n
 * hourColorRGB R G B\n
 * hourColorHSV H S V\n
 * minuteColorRGB R G B\n
 * minuteColorHSV H S V\n
 * secondColorRGB R G B\n
 * secondColorHSV H S V\n
 * hourWidth W\n
 * minuteWidth W\n
 * secondWidth W\n
 *
 * fullRGBColor R G B\n
 */

class CommandInterpreter
{
public:
    CommandInterpreter( LEDStripe& LEDStripeInner,
                        LEDStripe& LEDStripeOuter,
                        int minimalOutput = 30 );
    ~CommandInterpreter();

    void interpret( String const & command );

private:

    void clockHand( LEDStripe& stripe, int value, Color color, int max );

    void updatePixels();

    void parseColorRGB( String& arguments, Color& color );
    void parseColorHSV( String& arguments, Color& color );

    void setMode( String& arguments );
    void setTime( String& arguments );
    void setHourRGBColor( String& arguments );
    void setMinuteRGBColor( String& arguments );
    void setSecondRGBColor( String& arguments );
    void setHourHSVColor( String& arguments );
    void setMinuteHSVColor( String& arguments );
    void setSecondHSVColor( String& arguments );
    void setBackgroundRGBColor( String& arguments );
    void setBackgroundHSVColor( String& arguments );

    void setFullRGBColor( String& arguments );
    void setFullHSVColor( String& arguments );

    void fillRGBRow( String& arguments );
    void fillHSVRow( String& arguments );

    void setRGBPixel( String& arguments );
    void setHSVPixel( String& arguments );

    void setStripe( String& arguments );

    enum LogoMode
    {
        LogoModeGeneric,
        LogoModeClock
    };

    enum StripeType
    {
        StripeInner,
        StripeOuter
    };

    LEDStripe& m_LEDStripeInner;
    LEDStripe& m_LEDStripeOuter;
    LogoMode m_mode;
    StripeType m_stripeType;

    int m_hour;
    int m_minute;
    int m_second;

    Color m_hourColor;
    Color m_minuteColor;
    Color m_secondColor;

    Color m_backgroundColorInner;
    Color m_backgroundColorOuter;

    int m_hourWidth;
    int m_minuteWidth;
    int m_secondWidth;

    int m_minimalOutput;
};

#endif // __COMMAND_INTERPRETER_H__
