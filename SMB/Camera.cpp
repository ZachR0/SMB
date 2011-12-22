#include "Camera.h"

namespace SMB
{
    namespace Camera
    {
        //Camera Viewing Window
        SDL_Rect cameraRect;
        
        //Initializes Camera
        void Init()
        {
            //Setup Camera Rect
            cameraRect.w = SDL_GetVideoSurface()->w; //Screen Width
            cameraRect.h = SDL_GetVideoSurface()->h; //Screen Height
            cameraRect.x = 0;
            cameraRect.y = 0;
        }
        
        //Updates Camera X
        void setX(int x)
        {
            cameraRect.x = x;
        }
        
        //Gets Camera X
        int getX()
        {
            return cameraRect.x;
            
        }
        
        //Updates Camera Y
        void setY(int y)
        {
            cameraRect.y = y;
        }
        
        //Gets Camera Y
        int getY()
        {
            return cameraRect.y;
        }
    }
}