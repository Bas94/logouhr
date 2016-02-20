#include "CommandInterpreter.h"

#include "StringOperations.h"

CommandInterpreter::CommandInterpreter( LEDStripe& LEDStripeInner,
                                        LEDStripe& LEDStripeOuter )
    : m_LEDStripeInner( LEDStripeInner )
    , m_LEDStripeOuter( LEDStripeOuter )
    , m_mode( LogoModeClock )
    , m_hour( 0 )
    , m_minute( 0 )
    , m_second( 0 )
    , m_hourWidth( 2 )
    , m_minuteWidth( 2 )
    , m_secondWidth( 2 )
{
    m_hourColor.r = 0;
    m_hourColor.g = 0;
    m_hourColor.b = 80;

    m_minuteColor.r = 0;
    m_minuteColor.g = 80;
    m_minuteColor.b = 0;

    m_secondColor.r = 80;
    m_secondColor.g = 0;
    m_secondColor.b = 0;
}

CommandInterpreter::~CommandInterpreter()
{

}

/*!
 * \brief The CommandInterpreter class
 *
 * Protocol:
 * mode generic/clock
 * time HH MM SS\n
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
 */
void CommandInterpreter::interpret( String const & command )
{
    String rest = command;
    String type;
    strOp::split( rest, type, rest, ' ' );
    if( type.equals( "mode" ) ) { setMode( rest ); }
    else if( type.equals( "time" ) ) { setTime( rest ); }
    else if( type.equals( "clock" ) ) { setTime( rest ); }
    else if( type.equals( "hourColorRGB" ) ) { setHourRGBColor( rest ); }
    else if( type.equals( "minuteColorRGB" ) ) { setMinuteRGBColor( rest ); }
    else if( type.equals( "secondColorRGB" ) ) { setSecondRGBColor( rest ); }
    else if( type.equals( "hourColorHSV" ) ) { setHourHSVColor( rest ); }
    else if( type.equals( "minuteColorHSV" ) ) { setMinuteHSVColor( rest ); }
    else if( type.equals( "secondColorHSV" ) ) { setSecondHSVColor( rest ); }
    else if( type.equals( "fullRGBColor" ) ) { setFullRGBColor( rest ); }

    updatePixels();
}

void CommandInterpreter::clockHand( LEDStripe& stripe, int value, Color color, int max )
{
    float hPercent = static_cast<float>( value % max ) / max;
    float hfPos = stripe.getNumberOfPixels() * hPercent;
    int hPosHalf1 = static_cast<int>( hfPos );
    float half1perc = 1.0f - ( hfPos - hPosHalf1 );

    stripe.addRGBColor( hPosHalf1,
                        static_cast<int>( half1perc * color.r ),
                        static_cast<int>( half1perc * color.g ),
                        static_cast<int>( half1perc * color.b ) );

    if( half1perc < 1.0f )
    {
        int hPosHalf2 = static_cast<int>( hfPos+1 );
        float half2perc = 1.0f - half1perc;

        stripe.addRGBColor( hPosHalf2,
                            static_cast<int>( half2perc * color.r ),
                            static_cast<int>( half2perc * color.g ),
                            static_cast<int>( half2perc * color.b ) );
    }
}

void CommandInterpreter::updatePixels()
{
    if( m_mode == LogoModeClock )
    {
        m_LEDStripeInner.addFullRGBColor( 30, 30, 30 );
        m_LEDStripeOuter.addFullRGBColor( 30, 30, 30 );

        // hours
        clockHand( m_LEDStripeInner,
                   m_hour,
                   m_hourColor,
                   12 );

        // minutes
        clockHand( m_LEDStripeOuter,
                   m_minute,
                   m_minuteColor,
                   60 );

        // seconds
        clockHand( m_LEDStripeOuter,
                   m_second,
                   m_secondColor,
                   60 );

        m_LEDStripeInner.refresh();
        m_LEDStripeOuter.refresh();

    }
    else if( m_mode == LogoModeGeneric )
    {

    }
}

void CommandInterpreter::parseColorRGB( String& arguments, Color& color )
{
    String r,g,b;
    strOp::split( arguments, r, arguments, ' ' );
    strOp::split( arguments, g, b, ' ' );

    if( r.length() > 0 &&
        g.length() > 0 &&
        b.length() > 0 )
    {
        color.r = r.toInt();
        color.g = g.toInt();
        color.b = b.toInt();
    }
}

void CommandInterpreter::parseColorHSV( String& arguments, Color& color )
{
    String h,s,v;
    strOp::split( arguments, h, arguments, ' ' );
    strOp::split( arguments, s, v, ' ' );

    if( h.length() > 0 &&
        s.length() > 0 &&
        v.length() > 0 )
    {
        ColorOp::HSVtoRGB( h.toInt(), s.toInt(), v.toInt(),
                           color.r, color.g, color.b );
    }
}

void CommandInterpreter::setMode( String& arguments )
{
    arguments.trim();
    if( arguments.equals( "generic" ) )
    {
        m_mode = LogoModeGeneric;
    }
    else if( arguments.equals( "clock" ) )
    {
        m_mode = LogoModeClock;
    }
}

void CommandInterpreter::setTime( String& arguments )
{
    arguments.trim();
    String hour;
    String minute;
    String second;
    strOp::split( arguments, hour, arguments, ' ' );
    strOp::split( arguments, minute, second, ' ' );

    if( hour.length() > 0 &&
        minute.length() > 0 &&
        second.length() > 0 )
    {
        m_hour = hour.toInt();
        m_minute = minute.toInt();
        m_second = second.toInt();
    }
}

void CommandInterpreter::setHourRGBColor( String& arguments )
{
    parseColorRGB( arguments, m_hourColor );
}

void CommandInterpreter::setMinuteRGBColor( String& arguments )
{
    parseColorRGB( arguments, m_minuteColor );
}

void CommandInterpreter::setSecondRGBColor( String& arguments )
{
    parseColorRGB( arguments, m_secondColor );
}

void CommandInterpreter::setHourHSVColor( String& arguments )
{
    parseColorHSV( arguments, m_hourColor );
}

void CommandInterpreter::setMinuteHSVColor( String& arguments )
{
    parseColorHSV( arguments, m_minuteColor );
}

void CommandInterpreter::setSecondHSVColor( String& arguments )
{
    parseColorHSV( arguments, m_secondColor );
}

void CommandInterpreter::setFullRGBColor( String& arguments )
{
    Color col;
    parseColorRGB( arguments, col );
    m_LEDStripeInner.setFullRGBColor( col.r, col.g, col.b );
    m_LEDStripeOuter.setFullRGBColor( col.r, col.g, col.b );
}
