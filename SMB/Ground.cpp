#include "Ground.h"
#include "Game.h"

namespace SMB 
{
    namespace Levels
    {
        namespace Overlays
        {
            namespace Ground
            {
                //Handles Collision Trigger
                void Trigger()
                {
                    //Disable Player Gravity
                    Game::MainPlayer.Gravity_Enabled = false;
                }
                
                //Handles Collision DeTrigger
                void DeTrigger()
                {
                    //Enable Player Gravity
                    Game::MainPlayer.Gravity_Enabled = true;
                }
            }
        }
    }
}