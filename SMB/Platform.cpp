#include "Platform.h"
#include "Game.h"

namespace SMB 
{
    namespace Levels
    {
        namespace Overlays
        {
            namespace Platform
            {
                //Handles Platform Trigger
                void Trigger()
                {
                    //Disable Player Gravity
                    Game::MainPlayer.Gravity_Enabled = false;
                }
                
                //Handles Platform DeTrigger
                void DeTrigger()
                {
                    //Enable Player Gravity
                    Game::MainPlayer.Gravity_Enabled = true;
                }
            }
        }
    }
}