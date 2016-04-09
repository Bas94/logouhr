#include "CommandInterpreter.h"

#include "StringOperations.h"

CommandInterpreter::CommandInterpreter( LEDStripe& LEDStripeInner,
                                        LEDStripe& LEDStripeOuter,
                                        int minimalOutput )
    : m_LEDStripeInner( LEDStripeInner )
    , m_LEDStripeOuter( LEDStripeOuter )
    , m_mode( LogoModeClock )
    , m_stripeType( StripeOuter )
    , m_hour( 0 )
    , m_minute( 0 )
    , m_second( 0 )
    , m_hourWidth( 2 )
    , m_minuteWidth( 2 )
    , m_secondWidth( 2 )
    , m_minimalOutput( minimalOutput )
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

    m_backgroundColorOuter.r = 80;
    m_backgroundColorOuter.g = 80;
    m_backgroundColorOuter.b = 80;

    m_backgroundColorInner.r = 80;
    m_backgroundColorInner.g = 80;
    m_backgroundColorInner.b = 80;
}

CommandInterpreter::~CommandInterpreter()
{

}

/*!
 * \brief The CommandInterpreter class
 *
 * Protocol:
 * mode generic/clock
 *
 * CLOCK:
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
 *
 * backgroundRGBColor R G B\n
 * backgroundHSVColor H S V\n
 *
 * GENERIC:
 * setStripe inner/outer\n
 * fullRGBColor R G B\n
 * fullHSVColor H S V\n
 * fillRGBRow start end R G B\n
 * fillHSVRow start end H S V\n
 * setRGBPixel pos R G B\n
 * setHSVPixel pos H S V\n
 *
 */

void CommandInterpreter::interpret( String const & command )
{
    String rest, type;
    strOp::split( command, type, rest, ' ' );
    if( type.equals( "mode" ) )                { setMode( rest ); }
    else if( type.equals( "time" ) )           { setTime( rest ); }
    else if( type.equals( "clock" ) )          { setTime( rest ); }
    else if( type.equals( "hourColorRGB" ) )   { setHourRGBColor( rest ); }
    else if( type.equals( "minuteColorRGB" ) ) { setMinuteRGBColor( rest ); }
    else if( type.equals( "secondColorRGB" ) ) { setSecondRGBColor( rest ); }
    else if( type.equals( "hourColorHSV" ) )   { setHourHSVColor( rest ); }
    else if( type.equals( "minuteColorHSV" ) ) { setMinuteHSVColor( rest ); }
    else if( type.equals( "secondColorHSV" ) ) { setSecondHSVColor( rest ); }
    else if( type.equals( "backgroundRGBColor" ) ) { setBackgroundRGBColor( rest ); }
    else if( type.equals( "backgroundHSVColor" ) ) { setBackgroundHSVColor( rest ); }
    else if( type.equals( "setStripe" ) )      { setStripe( rest ); }
    else if( type.equals( "fullRGBColor" ) )   { setFullRGBColor( rest ); }
    else if( type.equals( "fullHSVColor" ) )   { setFullHSVColor( rest ); }
    else if( type.equals( "fillRGBRow" ) )     { fillRGBRow( rest ); }
    else if( type.equals( "fillHSVRow" ) )     { fillHSVRow( rest ); }
    else if( type.equals( "setRGBPixel" ) )    { setRGBPixel( rest ); }
    else if( type.equals( "setHSVPixel" ) )    { setHSVPixel( rest ); }
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
        m_LEDStripeInner.addFullRGBColor( m_backgroundColorInner.r, m_backgroundColorInner.g, m_backgroundColorInner.b );
        m_LEDStripeOuter.addFullRGBColor( m_backgroundColorOuter.r, m_backgroundColorOuter.g, m_backgroundColorOuter.b );

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

    int colorSum = color.r + color.g + color.b;
    if( colorSum < m_minimalOutput )
    {
       if( colorSum == 0 )
       {
           color.r = m_minimalOutput / 3 + 1;
           color.g = m_minimalOutput / 3 + 1;
           color.b = m_minimalOutput / 3 + 1;
       }
       else
       {
           color.r = color.r * m_minimalOutput / colorSum;
           color.g = color.g * m_minimalOutput / colorSum;
           color.b = color.b * m_minimalOutput / colorSum;
       }
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

void CommandInterpreter::setBackgroundRGBColor( String& arguments )
{
    Color color;
    parseColorRGB( arguments, color );
    if( m_stripeType == StripeInner )
    {
        m_backgroundColorInner = color;
    }
    else if( m_stripeType == StripeOuter )
    {
        m_backgroundColorOuter = color;
    }
}

void CommandInterpreter::setBackgroundHSVColor( String& arguments )
{
    Color color;
    parseColorHSV( arguments, color );
    if( m_stripeType == StripeInner )
    {
        m_backgroundColorInner = color;
    }
    else if( m_stripeType == StripeOuter )
    {
        m_backgroundColorOuter = color;
    }
}

void CommandInterpreter::setFullRGBColor( String& arguments )
{
    Color col;
    parseColorRGB( arguments, col );
    if( m_stripeType == StripeInner )
    {
        m_LEDStripeInner.setFullRGBColor( col.r, col.g, col.b );
    }
    else if( m_stripeType == StripeOuter )
    {
        m_LEDStripeOuter.setFullRGBColor( col.r, col.g, col.b );
    }
}

void CommandInterpreter::setFullHSVColor( String& arguments )
{
    Color col;
    parseColorHSV( arguments, col );
    if( m_stripeType == StripeInner )
    {
        m_LEDStripeInner.setFullRGBColor( col.r, col.g, col.b );
    }
    else if( m_stripeType == StripeOuter )
    {
        m_LEDStripeOuter.setFullRGBColor( col.r, col.g, col.b );
    }
}

void CommandInterpreter::setStripe( String& arguments )
{
    if( arguments == "outer" )
    {
        m_stripeType = StripeOuter;
    }

    if( arguments == "inner" )
    {
        m_stripeType = StripeInner;
    }
}

void CommandInterpreter::fillRGBRow( String& arguments )
{
    String start, end;
    Color col;
    strOp::split( arguments, start, arguments, ' ' );
    strOp::split( arguments, end, arguments, ' ' );
    parseColorRGB( arguments, col );
    if( start.length() > 0 && end.length() > 0 )
    {
        int startIndex = start.toInt();
        int endIndex = end.toInt();
        if( m_stripeType == StripeInner )
        {
            m_LEDStripeInner.setRGBLineColor( startIndex, endIndex, col.r, col.g, col.b );
        }
        else if( m_stripeType == StripeOuter )
        {
            m_LEDStripeOuter.setRGBLineColor( startIndex, endIndex, col.r, col.g, col.b );
        }
    }
}

void CommandInterpreter::fillHSVRow( String& arguments )
{
    String start, end;
    Color col;
    strOp::split( arguments, start, arguments, ' ' );
    strOp::split( arguments, end, arguments, ' ' );
    parseColorHSV( arguments, col );
    if( start.length() > 0 && end.length() > 0 )
    {
        int startIndex = start.toInt();
        int endIndex = end.toInt();
        if( m_stripeType == StripeInner )
        {
            m_LEDStripeInner.setRGBLineColor( startIndex, endIndex, col.r, col.g, col.b );
        }
        else if( m_stripeType == StripeOuter )
        {
            m_LEDStripeOuter.setRGBLineColor( startIndex, endIndex, col.r, col.g, col.b );
        }
    }
}

void CommandInterpreter::setRGBPixel( String& arguments )
{
    String indexStr;
    Color col;
    strOp::split( arguments, indexStr, arguments, ' ' );
    parseColorRGB( arguments, col );
    if( indexStr.length() > 0 )
    {
        int index = indexStr.toInt();
        if( m_stripeType == StripeInner )
        {
            m_LEDStripeInner.setRGBColor( index, col.r, col.g, col.b );
        }
        else if( m_stripeType == StripeOuter )
        {
            m_LEDStripeOuter.setRGBColor( index, col.r, col.g, col.b );
        }
    }
}

void CommandInterpreter::setHSVPixel( String& arguments )
{
    String indexStr;
    Color col;
    strOp::split( arguments, indexStr, arguments, ' ' );
    parseColorHSV( arguments, col );
    if( indexStr.length() > 0 )
    {
        int index = indexStr.toInt();
        if( m_stripeType == StripeInner )
        {
            m_LEDStripeInner.setRGBColor( index, col.r, col.g, col.b );
        }
        else if( m_stripeType == StripeOuter )
        {
            m_LEDStripeOuter.setRGBColor( index, col.r, col.g, col.b );
        }
    }
}
