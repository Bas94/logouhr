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
    m_hourColor = ColorHSV( 240, 255, 255 );

    m_minuteColor = ColorHSV( 120, 255, 255 );

    m_secondColor = ColorHSV( 0, 255, 255 );

    m_backgroundColorOuter = ColorHSV( 0, 0, 50 );

    m_backgroundColorInner = ColorHSV( 0, 0, 50 );
}

CommandInterpreter::~CommandInterpreter()
{

}

void CommandInterpreter::interpret( String const & topic, String const & message )
{
    String valuePath, valueName;
    strOp::splitFromEnd( topic, valuePath, valueName, '/' );
    if( valuePath.equals( "Netz39/Service/Clock/Wallclock/Simple" ) )
    {
        if( valueName.equals( "Second" ) )
        {
            m_second = message.toInt();
        }
        else if( valueName.equals( "Minute" ) )
        {
            m_minute = message.toInt();
        }
        else if( valueName.equals( "Hour" ) )
        {
            m_hour = message.toInt();
        }
    }
    else if( valuePath.equals( "Netz39/Things/Logouhr/Background" ) )
    {
        messageToHSVColor( valueName, message, m_backgroundColorOuter );
        //m_backgroundColorOuter.v = static_cast<int>( min( max( m_backgroundColorOuter.v, 1 ), 4 ) ) * 255 / 4;
        m_backgroundColorInner = m_backgroundColorOuter;
    }
    else if( valuePath.equals( "Netz39/Things/Logouhr/HourHand" ) )
    {
        messageToHSVColor( valueName, message, m_hourColor );
    }
    else if( valuePath.equals( "Netz39/Things/Logouhr/MinuteHand" ) )
    {
        messageToHSVColor( valueName, message, m_minuteColor );
    }
    else if( valuePath.equals( "Netz39/Things/Logouhr/SecondHand" ) )
    {
        messageToHSVColor( valueName, message, m_secondColor );
    }
    else if( valuePath.equals( "Netz39/Things/Logouhr" ) )
    {
        if( valueName.equals( "Mode" ) )
        {
            setMode( message );
        }
    }

    updatePixels();
}

void CommandInterpreter::messageToHSVColor(const String &valueName, const String &message, ColorHSV &color)
{
    if( valueName.equals( "Hue" ) )
    {
        color.h = message.toInt();
    }
    else if( valueName.equals( "Saturation" ) )
    {
        color.s = message.toInt();
    }
    else if( valueName.equals( "Value" ) )
    {
        color.v = message.toInt();
    }
}

void CommandInterpreter::clockHand( LEDStripe& stripe, int value, ColorHSV color, int max )
{
   // stripe.addHSVColor( value * stripe.getNumberOfPixels() / max,
   //                     static_cast<int>( color.h ),
   //                     static_cast<int>( color.s ),
   //                     static_cast<int>( color.v ) );

    float hPercent = static_cast<float>( value % max ) / max;
    float hfPos = stripe.getNumberOfPixels() * hPercent;
    int hPosHalf1 = static_cast<int>( hfPos );
    float half1perc = 1.0f - ( hfPos - hPosHalf1 );

    stripe.addHSVColor( hPosHalf1,
                        static_cast<int>( color.h ),
                        static_cast<int>( color.s ),
                        static_cast<int>( color.v ) );

    if( half1perc < 1.0f )
    {
        int hPosHalf2 = static_cast<int>( hfPos+1 );
        float half2perc = 1.0f - half1perc;

        stripe.addHSVColor( hPosHalf2,
                            static_cast<int>( color.h ),
                            static_cast<int>( color.s ),
                            static_cast<int>( color.v ) );
    }
}

void CommandInterpreter::updatePixels()
{
    if( m_mode == LogoModeClock )
    {
        m_LEDStripeInner.addFullHSVColor( m_backgroundColorInner.h, m_backgroundColorInner.s, m_backgroundColorInner.v );
        m_LEDStripeOuter.addFullHSVColor( m_backgroundColorOuter.h, m_backgroundColorOuter.s, m_backgroundColorOuter.v );

        // hours
        clockHand( m_LEDStripeInner,
                   m_hour,
                   m_hourColor,
                   12 );

        // minutes
        clockHand( m_LEDStripeOuter,
                   m_minute,
                   ColorHSV( 100, 255, 255 ), //m_minuteColor,
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

void CommandInterpreter::setMode( String const & arguments )
{
    if( arguments.equals( "generic" ) )
    {
        m_mode = LogoModeGeneric;
    }
    else if( arguments.equals( "clock" ) )
    {
        m_mode = LogoModeClock;
    }
}
