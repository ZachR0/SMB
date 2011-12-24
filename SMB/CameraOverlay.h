#ifndef SMB_CameraOverlay_h
#define SMB_CameraOverlay_h

#include <SDL/SDL.h>
#include <iostream>

using namespace std;

namespace SMB 
{
    namespace Levels
    {
        namespace Overlays
        {
            namespace Camera
            {
                //Handles Camera Overlay Trigger
                void Trigger(SDL_Rect rect);
                
                //Handles Camera Overlay DeTrigger
                void DeTrigger();
            }
        }
    }
}

#endif
