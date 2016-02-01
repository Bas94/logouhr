#ifndef __WIFI_H__
#define __WIFI_H__

#include <WString.h>
#include <ESP8266WiFi.h>

class Wifi
{
public:
    Wifi();
    Wifi( String name, String password, bool accessPoint );

    bool openAccessPoint( String name, String password );
    bool connectToWLAN( String name, String password ,uint8_t connectAttempts );

    bool disconnect();
    bool isConnected();

    IPAddress getIP();

private:
    bool m_isAccessPoint;
    bool m_connected;
};

#endif
