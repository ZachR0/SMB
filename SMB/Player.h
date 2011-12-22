#ifndef SMB_Player_h
#define SMB_Player_h

#include "Sprites.h"

#include <SDL/SDL.h>

namespace SMB
{
    namespace Player
    {
        class Player
        {
        private:
            Sprites::Sprite sprite; //Player Sprite
            int x, y; //Player x,y cords
            int speed; //Player move speed
            
        public:
            //Bounding Box Collision Rect
            SDL_Rect CollisionRect;
            
            //Gravity Enable / Disable
            bool Gravity_Enabled;
            
            //Initialization
            void Init(string SpriteSheet, string SpriteMap);
            
            //Movement
            void MoveRight();
            void MoveLeft();
            void MoveStop();
            
            //Returns Movement Direction
            int GetMoveDirection();
            
            //Manually set player location
            void SetCords(int x, int y);
            
            //Get x cord
            int GetX();
            
            //Get y cord
            int GetY();
            
            //Sets movement speed
            void SetMoveSpeed(int speed);
            
            //Gets movement speed
            int GetMoveSpeed();
            
            //Sets the Camera System to follow us
            void SetCamera();
            
            //Animation
            void Animate();
            
            //Render
            void Render();
            
            //Gravity Management
            void Gravity();
        };
    }
}


#endif
