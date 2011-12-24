#include "CameraOverlay.h"
#include "Camera.h"
#include "Game.h"

namespace SMB 
{
    namespace Levels
    {
        namespace Overlays
        {
            namespace Camera
            {
                //Handles Camera Overlay Trigger
                void Trigger(SDL_Rect rect)
                {                    
                    //Disable Default Camera Settings
                    Game::MainPlayer.Camera_Default = false;
                    
                    //Camera over player
                    SMB::Camera::setX(rect.x);
                    SMB::Camera::setY(rect.y);
                }
                
                //Handles Camera Overlay DeTrigger
                void DeTrigger()
                {
                    //Enable Default Camera Settings
                    Game::MainPlayer.Camera_Default = true;
                    
                    //Reset Camera Defaults
                    SMB::Camera::Init();
                }
            }
        }
    }
}