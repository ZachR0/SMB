#ifndef SMB_Camera_h
#define SMB_Camera_h

#include <SDL/SDL.h>


namespace SMB
{
    namespace Camera
    {
        //Camera Viewing Window
        extern SDL_Rect cameraRect;
        
        //Initializes Camera
        void Init();
        
        //Updates Camera X
        void setX(int x);
        
        //Gets Camera X
        int getX();
        
        //Updates Camera Y
        void setY(int y);
        
        //Gets Camera Y
        int getY();
    }
}

#endif
