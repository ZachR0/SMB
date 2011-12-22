#ifndef SMB_FPS_h
#define SMB_FPS_h

#include "Timer.h"

#include <SDL/SDL.h>

namespace SMB
{
    namespace FPS
    {
        //Target FPS Cap
        extern int FRAMES_PER_SECOND;
        
        //Calculated FPS
        extern int CALC_FPS;
        
        //FPS Regulation Timer
        extern Timer fps;
        
        //Initializes FPS awesomeness
        void Init(int target_fps);
        
        //Checks if FPS needs to be regulated, and handles such
        void Check();
        
        //Gets current calculated FPS
        int CalculateFPS();
        
        //Gets the target FPS
        int TargetFPS();
        
        //Sets the target FPS
        void SetTargetFPS(int target_fps);
        
    }
}


#endif
