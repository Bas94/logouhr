#ifndef __STRING_OPERATIONS_H__
#define __STRING_OPERATIONS_H__

#include <WString.h>

namespace strOp
{

    void split( String& str1, String& str2, char splitChar );

    void parseInput( String input, int& red, int& green, int& blue );
}

#endif // __STRING_OPERATIONS_H__
