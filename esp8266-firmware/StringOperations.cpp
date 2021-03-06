#include "StringOperations.h"

namespace strOp
{

    void split( String& str1, String& str2, char splitChar )
    {
        int indx = str1.indexOf( splitChar );
        if( indx < 0 )
        {
            str2 = "";
            return;
        }
        str2 = str1.substring( indx+1, str1.length() );
        str1 = str1.substring( 0, indx );
    }

    void split( String const & input, String& str1, String& str2, char splitChar )
    {
        String cpy = input;
        int indx = cpy.indexOf( splitChar );
        if( indx < 0 )
        {
            str1 = "";
            str2 = "";
            return;
        }
        str2 = cpy.substring( indx+1, cpy.length() );
        str1 = cpy.substring( 0, indx );
    }

    void splitFromEnd(String &str1, String &str2, char splitChar)
    {
        int indx = str1.lastIndexOf( splitChar );
        if( indx < 0 )
        {
            str2 = "";
            return;
        }
        str2 = str1.substring( indx+1, str1.length() );
        str1 = str1.substring( 0, indx );
    }

    void splitFromEnd(const String &input, String &str1, String &str2, char splitChar)
    {
        String cpy = input;
        int indx = cpy.lastIndexOf( splitChar );
        if( indx < 0 )
        {
            str1 = "";
            str2 = "";
            return;
        }
        str2 = cpy.substring( indx+1, cpy.length() );
        str1 = cpy.substring( 0, indx );
    }

    void parseInput( String input, int& red, int& green, int& blue )
    {
        String strRed = input, strGreen, strBlue;
        split( strRed, strGreen, ' ' );
        split( strGreen, strBlue, ' ' );
        if( strRed.length() == 0 || strGreen.length() == 0 || strBlue.length() == 0 )
        {
            red = 0;
            green = 0;
            blue = 0;
            return;
        }
        red = strRed.toInt();
        green = strGreen.toInt();
        blue = strBlue.toInt();
    }
}
