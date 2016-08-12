#include <WString.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

class MQTTClient
{
public:
    MQTTClient();
    ~MQTTClient();

    bool connect( String serverName,
                  int port, int numberOfreconnects );

    void publish( String topic, String message );


protected:
    WiFiClient m_espClient;
    PubSubClient m_client;
    String m_serverName;
    int m_port;
};
