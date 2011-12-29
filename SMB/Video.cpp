#include "Video.h"

namespace SMB
{
    namespace SDL
    {
        //Initializes SDL and its subsystems
        bool Init(int Screen_Width, int Screen_Height, int BPP)
        {
            //Initialize SDL subsystems
            if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
            {
                //Something went wrong
                return false;
            }
            
            //Setup Screen - Any issues, return false
            if((SDL_SetVideoMode(Screen_Width, Screen_Height, BPP, SDL_SWSURFACE | SDL_DOUBLEBUF)) == NULL) return false;
            
            //Initialize SDL_ttf
            if(TTF_Init() == -1)
            {
                return false;
            }
            
            //Enable Keyboard Input Repeat
            SDL_EnableKeyRepeat(1, 1);
            
            //Disable Cursor
            SDL_ShowCursor(false);

            //Set window caption
            SDL_WM_SetCaption("Super Mario Bros", NULL);
            
            
            //Assuming everything went well...
            return true;
        }
        
        //Deinitalizes SDL and its subsystems
        void DeInit()
        {
            //Quit SDL
            SDL_Quit();
            
            //Quit Subsystems
            TTF_Quit();
        }
    }
}