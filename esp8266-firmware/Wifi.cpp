#include "Wifi.h"

Wifi::Wifi()
    : m_isAccessPoint( false )
    , m_connected( false )
{

}

Wifi::Wifi( String name, String password, bool accessPoint )
    : m_isAccessPoint( accessPoint )
    , m_connected( false )
{
    if( m_isAccessPoint )
    {
        openAccessPoint( name, password );
    }
    else
    {
        connectToWLAN( name, password, 20 );
    }
}

bool Wifi::openAccessPoint( String name, String password )
{
    m_isAccessPoint = true;
    WiFi.mode(WIFI_AP);               // access point mode
    WiFi.softAP( name.c_str(), password.c_str() );    // Name of Wi-Fi netword
    delay( 500 );
    return true;
}

bool Wifi::connectToWLAN( String name, String password, uint8_t connectAttempts )
{
    m_isAccessPoint = false;
    WiFi.begin( name.c_str(), password.c_str() );
    //Serial.print("\nConnecting to "); Serial.println(ssid);
    // Wait for connection
    for( uint8_t i = 0; WiFi.status() != WL_CONNECTED && i <= connectAttempts; ++i )
    {
        delay ( 500 );
    }

    if( WiFi.status() != WL_CONNECTED )
    {
        return false;
    }

    //Serial.println( "connected" );
    //Serial.println(WiFi.localIP());
    return true;
}

bool Wifi::disconnect()
{
    WiFi.disconnect();
    return true;
}

bool Wifi::isConnected()
{
    return WiFi.status() == WL_CONNECTED;
}

IPAddress Wifi::getIP()
{
    if( m_isAccessPoint )
    {
        return WiFi.softAPIP();
    }
    else
    {
        return WiFi.localIP();
    }
}
