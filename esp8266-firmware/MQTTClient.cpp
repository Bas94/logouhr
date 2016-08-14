#include "MQTTClient.h"

#include "Wifi.h"
#include "WifiLogin.h"

void(*m_callback_t)( String&, String& ) = 0;

void callback(const MQTT::Publish& publish)
{
    String topic = publish.topic();
    String payloadString = publish.payload_string();
    if( m_callback_t )
        m_callback_t( topic, payloadString );
}


MQTTClient::MQTTClient( String server )
    : m_client( m_espClient, "helium" )
{

}

MQTTClient::~MQTTClient()
{

}

bool MQTTClient::connect( String serverName, int port, int numberOfreconnects )
{
    int reconnects = 0;
    //m_client.set_server( serverName, port );
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
    m_client.set_callback( callback );

    return true;
}

void MQTTClient::publish(String topic, String message)
{
    m_client.publish( topic, message );
}

void MQTTClient::subscribe( String topic )
{
    m_client.subscribe( topic );
}

void MQTTClient::setCallback(void (*callback_t)(String &, String &))
{
    m_callback_t = callback_t;
}

bool MQTTClient::loop()
{
    m_client.loop();
}

bool MQTTClient::isConnected()
{
    return m_client.connected();
}
