#include "TCPServer.h"

TCPServer::TCPServer( int port )
    : m_port( port )
    , m_server( port )
    , m_buffer( "" )
{
    m_server.begin();
    m_server.setNoDelay(true);
    serviceLoop();
}

void TCPServer::serviceLoop()
{
    if( !clientConnected() )
    {
        m_client = m_server.available();
    }

    if( clientConnected() )
    {
        uint16_t numBytes = m_client.available();
        for( uint16_t i = 0; i < numBytes; ++i )
        {
            m_buffer += m_client.read();
        }
    }
}

bool TCPServer::clientConnected()
{
    serviceLoop();
    return m_client && m_client.connected();
}

bool TCPServer::dataAvailable()
{
    serviceLoop();
    return m_buffer.length() > 0;
}

String TCPServer::readData()
{
    serviceLoop();
    String result = m_buffer;
    m_buffer = "";
    return result;
}

String TCPServer::getDataUntilCharacter( char splitCharacter )
{
    serviceLoop();
    int index = m_buffer.indexOf( splitCharacter );

    if( index < 0 )
        return "";

    String result = m_buffer.substring( 0, index );
    m_buffer = m_buffer.substring( index + 1, m_buffer.length() );
    return result;
}
