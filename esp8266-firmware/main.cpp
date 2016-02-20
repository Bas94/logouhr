#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include "LEDStripe.h"
#include "TCPServer.h"
#include "Wifi.h"
#include "WifiLogin.h"
#include "CommandInterpreter.h"

#include "StringOperations.h"


const char* ssid = SSID;
const char* password = PASSWORD;
const int tcpPort = 1337;

TCPServer server( tcpPort );
Wifi wifi;
LEDStripe stripeOuter( 5, 147 );
LEDStripe stripeInner( 4, 147 );

CommandInterpreter interpreter( stripeInner,
                                stripeOuter );

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

  server.start();

  Serial.println("Ready!");
  Serial.print("connect to ");
  Serial.print( wifi.getIP() );
  Serial.print( ":" );
  Serial.println( tcpPort );
}

void loop()
{
    delay( 1 );
    if( server.clientConnected() )
    {
        //Serial.println("connected.");
        if( server.dataAvailable()  )
        {
            String command = server.getDataUntilCharacter( '\n' );
            if( command.length() != 0 )
            {
                interpreter.interpret( command );
                // empty buffer
                server.readData();
            }
        }
    }
    else
    {
        Serial.print("connect to ");
        Serial.print( wifi.getIP() );
        Serial.print( ":" );
        Serial.println( tcpPort );
    }
}
