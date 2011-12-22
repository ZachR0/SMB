#ifndef SMB_Collision_h
#define SMB_Collision_h

#include <SDL/SDL.h>
#include <SDL/SDL_thread.h>

namespace SMB
{
    namespace Collision
    {
        //Thead for Checking and Handling Collision
        extern SDL_Thread *Handle_Monitor_Thread;
        
        //Initializes Collision
        void Init();
        
        //DeInitializes Collision
        void DeInit();
        
        //Thread for Monitoring and Handling Collision Events
        int Collision_Handle_Thread(void *data);
        
        //Checks for collision between two SDL_Rects (Basic bounding box collision)
        bool BoundingCheck(SDL_Rect A, SDL_Rect B);
    }
}


#endif
