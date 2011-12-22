#ifndef SMB_Video_h
#define SMB_Video_h

#include <SDL/SDL.h>
#include <SDL_ttf/SDL_ttf.h>

namespace SMB
{
    namespace SDL
    {
        //Initializes SDL and its subsystems
        bool Init(int Screen_Width, int Screen_Height, int BPP);
        
        //Deinitalizes SDL and its subsystems
        void DeInit();
    }
}


#endif
