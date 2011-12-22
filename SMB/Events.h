#ifndef SMB_Events_h
#define SMB_Events_h

#include <SDL/SDL.h>

namespace SMB
{
    namespace Events
    {
        //SDL Event Structure
        extern SDL_Event Event;
        
        //Handles all supported event input
        void Handle();
    }
}

#endif
