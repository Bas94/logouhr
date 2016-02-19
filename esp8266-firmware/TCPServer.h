#ifndef __TCP_SERVER_H__
#define __TCP_SERVER_H__

#include <WString.h>
#include <ESP8266WiFi.h>

class TCPServer
{
public:
    TCPServer( int port );

    bool start();

    //! return true if any client is currently connected to this TCPSocket
    bool clientConnected();

    //! returns true if the tcpServer has stored any data in his buffer
    bool dataAvailable();

    //! returns all data which is currently stored in his buffer
    //! the internal buffer will be emptied after calling this function
    String readData();

    //! returns data until a split character appears
    //! returns empty string if this character doesn't appear in the current buffer
    //! the returned string will be removed from the internal buffer
    String getDataUntilCharacter( char splitCharacter );

private:
    //! keeps this socket up to date
    void serviceLoop();

    int m_port;

    WiFiServer m_server;
    WiFiClient m_client;

    String m_buffer;
};

#endif // __TCP_SERVER_H__
