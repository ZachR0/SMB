#include <SDL/SDL.h>
#include <SDL/SDL_thread.h>
#include "Collision.h"
#include "Game.h"
#include "FPS.h"

namespace SMB
{
    namespace Collision
    {
        //Thead for Checking and Handling Collision
        SDL_Thread *Handle_Monitor_Thread;
        
        //Initializes Collision
        void Init()
        {
            //Start Collision Monitor and Handling Thread
            Handle_Monitor_Thread = NULL;
            Handle_Monitor_Thread = SDL_CreateThread(Collision_Handle_Thread, NULL);
        }
        
        //DeInitializes Collision
        void DeInit()
        {
            //Stop the Collision Monitor and Handling Thread (if it is still running)
            try
            {
                if(Handle_Monitor_Thread != NULL)
                {
                    //This SDL method is rather unstable 
                    //Collision thread handles its own exit
                    //SDL_KillThread(Handle_Monitor_Thread);
                }
            }
            catch(...)
            {
                //Do nothing
            }
        }
        
        //Thread for Monitoring and Handling Collision Events
        int Collision_Handle_Thread(void *data)
        {
            while(!Game::QUIT)
            {
                //Check against Object Layer Collision
                for(int i = 0; i < Game::Level.numObjs; i++)
                {
                    //Does the player collide with Object layer?
                    if(BoundingCheck(Game::MainPlayer.CollisionRect, Game::Level.Objects[i].rect))
                    {
                        //Call Object's Trigger Function
                        Game::Level.Objects[i].Trigger();
                    }
                    else
                    {
                        //Call Object's DeTrigger Function
                        Game::Level.Objects[i].DeTrigger();
                    }
                }
                
                //Delay Loop A Bit
                SDL_Delay(1);
            }
            
            return 0;
        }
        
        //Checks for collision between two SDL_Rects (Basic bounding box collision)
        bool BoundingCheck(SDL_Rect A, SDL_Rect B)
        {
            //The sides of the rectangles
            int leftA, leftB;
            int rightA, rightB;
            int topA, topB;
            int bottomA, bottomB;
            
            //Calculate the sides of rect A
            leftA = A.x;
            rightA = A.x + A.w;
            topA = A.y;
            bottomA = A.y + A.h;
            
            //Calculate the sides of rect B
            leftB = B.x;
            rightB = B.x + B.w;
            topB = B.y;
            bottomB = B.y + B.h;
            
            //If any of the sides from A are outside of B
            if(bottomA <= topB)
            {
                return false;
            }
            
            if(topA >= bottomB)
            {
                return false;
            }
            
            if(rightA <= leftB)
            {
                return false;
            }
            
            if(leftA >= rightB)
            {
                return false;
            }
            
            //If none of the sides from A are outside B (COLLISION :D)
            return true;
        }
        
        
    }
}