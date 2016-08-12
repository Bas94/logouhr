#include "MQTTClient.h"

#include "Wifi.h"
#include "WifiLogin.h"

MQTTClient::MQTTClient()
    : m_client( m_espClient )
{

}

MQTTClient::~MQTTClient()
{

}

bool MQTTClient::connect( String serverName, int port, int numberOfreconnects )
{
    int reconnects = 0;
    m_client.set_server( serverName, port );
    while (!m_client.connected())
    {
        if (!m_client.connect( String("logouhr") ) )
        {
            // Wait 5 seconds before retrying
            reconnects++;
            if( reconnects > numberOfreconnects )
                return false;
            delay(5000);
        }
    }
    return true;
}

void MQTTClient::publish(String topic, String message)
{
    m_client.publish( topic, message );
}
