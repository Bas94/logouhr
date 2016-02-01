#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include "StringOperations.h"

const char* ssid = "SSID";
const char* password = "PASSWORD";

WiFiServer server(1337);
WiFiUDP udpSender;
int redPin = 14;
int greenPin = 15;
int bluePin = 4;

void printWiFiStatus()
{
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("AP IP address: ");
  Serial.println( WiFi.softAPIP() );
  Serial.print("local IP address: ");
  Serial.println( WiFi.localIP() );
}

void initServerAP()
{
  WiFi.mode(WIFI_AP);           // access point modus
  WiFi.softAP("ESPAccess", "12345678");    // Name des Wi-Fi netzes
  delay(500);                   //Abwarten 0,5s
  Serial.print("IP Adresse ");  //Ausgabe aktueller IP des Servers
  Serial.println(WiFi.softAPIP());
  delay(500);
  printWiFiStatus();
}

void initWLANEntry()
{
  WiFi.begin(ssid, password);
  Serial.print("\nConnecting to "); Serial.println(ssid);
  uint8_t i = 0;
  // Wait for connection
  while ( WiFi.status() != WL_CONNECTED && i <= 20 )
  {
      delay ( 500 );
      Serial.print ( "." );
      i++;
  }
  Serial.println( "connected" );
  Serial.println(WiFi.localIP());
  if(i == 21)
  {
    Serial.print("Could not connect to "); Serial.println(ssid);
    while(1) delay(500);
  }
}

void setup()
{
  Serial.begin(115200);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  analogWrite(redPin, 0);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 0);

  //initServerAP();

  initWLANEntry();

  Serial.println("Ready!");
  //Serial.print( WiFi.localIP() );
  Serial.println(" 21' to connect");

  server.begin();
  server.setNoDelay(true);
}

void loop()
{
  String tcpRead = "";
  WiFiClient client = server.available();
  if (client)
  {
    Serial.println("Client connected.");
    while (client.connected())
    {
      delay( 1 );
      if (client.available())
      {
        char command = client.read();
        if( command != '\n' )
        {
          tcpRead += command;
        }
        else
        {
          int red, green, blue;
          strOp::parseInput( tcpRead, red, green, blue );
          tcpRead = "";
          analogWrite( redPin, red );
          analogWrite( greenPin, green );
          analogWrite( bluePin, blue );
        }
      }
    }
    Serial.println("Client disconnected.");
    client.stop();
  }
  else
  {
      printWiFiStatus();
  }
}

