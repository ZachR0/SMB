#ifndef Elysium_base64_h
#define Elysium_base64_h

#include <iostream>
#include <zlib.h>

using namespace std;

namespace SMB
{
    namespace Levels
    {
        namespace TMX //Tiled Map Editor
        {
            namespace Base64
            {
                //Encode / Decode Functions based from base64 (RFC 3548)
                void _base64_encode_triple(unsigned char triple[3], char result[4]);
                int base64_encode(unsigned char *source, size_t sourcelen, char *target, size_t targetlen);
                int _base64_char_value(char base64char);
                int _base64_decode_triple(char quadruple[4], unsigned char *result);
                size_t base64_decode(char *source, unsigned char *target, size_t targetlen);
            }
        }
    }
}

#endif
