#include "CollisionOverlay.h"
#include "Game.h"
#include "Sprites.h"

#include <iostream>
using namespace std;

namespace SMB 
{
    namespace Levels
    {
        namespace Overlays
        {
            namespace Collision
            {
                //Handles Collision Trigger
                void Trigger()
                {
                    //Correct Main Player's X,Y depending on the direction of movement on collision
                    if(Game::MainPlayer.GetMoveDirection() == RIGHT_DIRECTION)
                    {
                        Game::MainPlayer.SetCords(Game::MainPlayer.GetX() - Game::MainPlayer.GetMoveSpeed(), Game::MainPlayer.GetY());
                        
                    }
                    if(Game::MainPlayer.GetMoveDirection() == LEFT_DIRECTION)
                    {
                        Game::MainPlayer.SetCords(Game::MainPlayer.GetX() + Game::MainPlayer.GetMoveSpeed(), Game::MainPlayer.GetY());
                    }
                }
                
                //Handles Collision DeTrigger
                void DeTrigger()
                {
                    //Do nothing...
                }
            }
        }
    }
}