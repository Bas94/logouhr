#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include "LEDStripe.h"
#include "TCPServer.h"
#include "Wifi.h"
#include "WifiLogin.h"

#include "StringOperations.h"


const char* ssid = SSID;
const char* password = PASSWORD;
const int tcpPort = 1337;

TCPServer server( tcpPort );
Wifi wifi;
LEDStripe stripe( 5, 300 );

void setup()
{
  stripe.setFullRGBColor( 80, 80, 80 );
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
                int red, green, blue;
                strOp::parseInput( command, red, green, blue );
                stripe.setFullRGBColor( red, green, blue );
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

