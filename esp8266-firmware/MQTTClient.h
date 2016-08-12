#include <WString.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

class MQTTClient
{
public:
    MQTTClient( String server );
    ~MQTTClient();

    bool connect( String serverName,
                  int port, int numberOfreconnects );

    void publish( String topic, String message );
    void subscribe( String topic );

    void setCallback( void(*callback_t)( String&, String& ) );

    bool loop();

    bool isConnected();

protected:

    WiFiClient m_espClient;
    PubSubClient m_client;
    String m_serverName;
    int m_port;
};
