#include "FPS.h"

#include <SDL/SDL.h>

namespace SMB
{
    namespace FPS
    {
        //Target FPS Cap
        int FRAMES_PER_SECOND;
        
        //Calculated FPS
        int CALC_FPS;
        
        //FPS Regulation Timer
        Timer fps;
        
        int frames_drawn = 0;
        int fps_counter = 0;
        int prev_ticks = 0;
        
        //Initializes FPS awesomeness
        void Init(int target_fps)
        {
            FRAMES_PER_SECOND = target_fps;
            CALC_FPS = 0;
        }
        
        //Checks if FPS needs to be regulated, and handles such
        void Check()
        {
            //Do we need to cap the frame rate
            if(fps.get_ticks() < 1000 / FRAMES_PER_SECOND)
            {
                //Sleep the remaining frame time
                SDL_Delay( (1000 / FRAMES_PER_SECOND) - fps.get_ticks());
            }
            
            //Update frame drawn counter
            frames_drawn++;
            
            Uint32 ticks_now = SDL_GetTicks();
            Uint32 diff = ticks_now - prev_ticks;
            fps_counter += diff;
            prev_ticks = ticks_now;
            
            if(fps_counter >= 1000) 
            {
                CALC_FPS = (float)frames_drawn / (float)(fps_counter/1000.0f);
                frames_drawn = 0;
                fps_counter = 0;
            }
        }
        
        //Gets current calculated FPS
        int CalculateFPS()
        {
            return CALC_FPS;
        }
        
        //Gets the target FPS
        int TargetFPS()
        {
            return FRAMES_PER_SECOND;   
        }
        
        //Sets the target FPS
        void SetTargetFPS(int target_fps)
        {
            FRAMES_PER_SECOND = target_fps;
        }
    }
}