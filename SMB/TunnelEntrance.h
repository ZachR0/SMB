#ifndef SMB_TunnelEntrance_h
#define SMB_TunnelEntrance_h

#include <SDL/SDL.h>
#include <SDL/SDL_thread.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <sstream>

using namespace std;

namespace SMB 
{
    namespace Levels
    {
        namespace Overlays
        {
            namespace TunnelEntrance
            {
                //Keystate Activation Check Thread
                extern SDL_Thread *KeystateCheck;
                extern bool RUN_CHECK;
                
                //Handles Tunnel Entrance Trigger
                void Trigger(string Activate_Direction, string Port_Object);
                
                //Keystate Activation Check Thread
                int KeyState_Thread(void *data);
                
                //Handles Tunnel Entrance DeTrigger
                void DeTrigger();
            }
        }
    }
}

#endif
