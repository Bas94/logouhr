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
                        int minimalOutput = 10 );
    ~CommandInterpreter();

    void interpret( String const & topic, const String &message );

private:

    void messageToHSVColor( String const & valueName, String const & message, ColorHSV& color );
    void clockHand( LEDStripe& stripe, int value, ColorHSV color, int max );

    void updatePixels();

    void setMode( String const & arguments );

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

    ColorHSV m_hourColor;
    ColorHSV m_minuteColor;
    ColorHSV m_secondColor;

    ColorHSV m_backgroundColorInner;
    ColorHSV m_backgroundColorOuter;

    int m_hourWidth;
    int m_minuteWidth;
    int m_secondWidth;

    int m_minimalOutput;
};

#endif // __COMMAND_INTERPRETER_H__
