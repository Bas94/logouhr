#include "TCPServer.h"

TCPServer::TCPServer( int port )
    : m_port( port )
    , m_server( port )
    , m_buffer( "" )
{
}

void TCPServer::serviceLoop()
{
    if( clientConnected() )
    {
        uint16_t numBytes = m_client.available();
        for( uint16_t i = 0; i < numBytes; ++i )
        {
            m_buffer += String( static_cast<char>( m_client.read() ) );
        }
    }
}

bool TCPServer::start()
{
    m_server.begin();
    m_server.setNoDelay(true);
    serviceLoop();
}

bool TCPServer::clientConnected()
{
    if( !m_client || !m_client.connected() )
        m_client = m_server.available();

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
