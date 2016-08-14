#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include "LEDStripe.h"
#include "TCPServer.h"
#include "Wifi.h"
#include "WifiLogin.h"
#include "CommandInterpreter.h"

#include "StringOperations.h"
#include "MQTTClient.h"


const char* ssid = SSID;
const char* password = PASSWORD;
const int tcpPort = 1337;

Wifi wifi;
MQTTClient mqttClient( "helium" );
Adafruit_NeoPixel stripe( 294, 4, NEO_GRB + NEO_KHZ800 );
LEDStripeSnippet stripeInner( stripe, 0, 131 );
LEDStripeSnippet stripeOuter( stripe, 131, 146 );

CommandInterpreter interpreter( stripeInner,
                                stripeOuter,
                                10 );

void callback( String& topic, String& message )
{
    Serial.print(topic);
    Serial.print(":");
    Serial.println(message);

    interpreter.interpret( topic, message );
}

void setup()
{
  stripeOuter.setFullRGBColor( 80, 0, 0 );
  stripeInner.setFullRGBColor( 0, 0, 80 );
  delay( 500 );
  Serial.begin(115200);
  if( !wifi.connectToWLAN( ssid, password, 20 ) )
  {
      Serial.println("connection failed!");
      for(;;);
  }

  bool connected = false;
  //while( !connected )
  {
      connected = !mqttClient.connect( "helium", 1883, 5 );
  }
  stripeOuter.setFullRGBColor( 0, 80, 0 );
  mqttClient.setCallback( callback );
  mqttClient.subscribe( "Netz39/Things/Logouhr/#" );
  mqttClient.subscribe( "Netz39/Service/Clock/Wallclock/Simple/#" );

  Serial.println("Ready!");
  Serial.print("connect to ");
  Serial.print( wifi.getIP() );
  Serial.print( ":" );
  Serial.println( tcpPort );

  stripeOuter.refresh();
  stripeInner.refresh();
}

int i = 0;
void loop()
{
    delay( 1 );
    if( mqttClient.isConnected() )
    {
        mqttClient.loop();
    }
    else
    {
        mqttClient.connect( "helium", 1883, 5 );
        mqttClient.subscribe( "Netz39/Things/Logouhr/#" );
        mqttClient.subscribe( "Netz39/Service/Clock/Wallclock/Simple/#" );
    }
}
