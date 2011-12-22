#include "Player.h"
#include "Camera.h"
#include "Game.h"

namespace SMB
{
    namespace Player
    {
        //Initialization
        void Player::Init(string SpriteSheet, string SpriteMap)
        {
            //Load Player Sprite
            this->sprite.Load(SpriteSheet, SpriteMap);
            
            //Set Variables (Default Values)
            this->x = 0;
            this->y = 0;
            this->speed = 2;
            this->Gravity_Enabled = true;
            
            //Disable Animation (Will reenable upon player movement)
            this->sprite.SetAnimate(false);
            
            //Default Direction
            this->sprite.SetDirection(RIGHT_DIRECTION);
            
            //Update Collision Rect
            CollisionRect.x = this->x;
            CollisionRect.y = this->y;
            CollisionRect.w = this->sprite.GetFrameSurface(this->sprite.GetFrame())->w;
            CollisionRect.h = this->sprite.GetFrameSurface(this->sprite.GetFrame())->h;
        }
        
        //Movement
        void Player::MoveRight()
        {
            //Update x
            this->x += this->speed;
            
            //Update Animation Direction
            this->sprite.SetDirection(RIGHT_DIRECTION);
            
            //Enable Animation
            this->sprite.SetAnimate(true);
            
            //Update Collision Rect
            CollisionRect.x = this->x;
            CollisionRect.y = this->y;
        }
        void Player::MoveLeft()
        {
            //Update x
            this->x -= this->speed;
            
            //Update Animation Direction
            this->sprite.SetDirection(LEFT_DIRECTION);
            
            //Enable Animation
            this->sprite.SetAnimate(true);
            
            //Update Collision Rect
            CollisionRect.x = this->x;
            CollisionRect.y = this->y;
        }
        void Player::MoveStop()
        {
            //Disable Animation
            this->sprite.SetAnimate(false);
            
            //Update Collision Rect
            CollisionRect.x = this->x;
            CollisionRect.y = this->y;
        }
        
        //Returns Movement Direction
        int Player::GetMoveDirection()
        {
            return this->sprite.GetDirection();
        }
        
        //Manually set player location
        void Player::SetCords(int x, int y)
        {
            this->x = x;
            this->y = y;
            
            //Update Collision Rect
            CollisionRect.x = this->x;
            CollisionRect.y = this->y;
        }
        
        //Get x cord
        int Player::GetX()
        {
            return this->x;
        }
        
        //Get y cord
        int Player::GetY()
        {
            return this->y;
        }
        
        //Sets movement speed
        void Player::SetMoveSpeed(int speed)
        {
            this->speed = speed;
        }
        
        //Gets movement speed
        int Player::GetMoveSpeed()
        {
            return this->speed;
        }
        
        //Sets the Camera System to follow us
        void Player::SetCamera()
        {
            //Camera over player
            Camera::setX(this->x  - SDL_GetVideoSurface()->w / 2);
            Camera::setY(this->y - (Game::Level.MAP_HEIGHT - SDL_GetVideoSurface()->h));
            
            //Keep Camera in bounds
            if(Camera::getX() < 0)
            {
                Camera::setX(0);
            }
            if(Camera::getY() < 0)
            {
                Camera::setY(0);
            }
            if(Camera::getX() > Game::Level.MAP_WIDTH - Camera::cameraRect.w)
            {
                Camera::setX(Game::Level.MAP_WIDTH - Camera::cameraRect.w);
            }
            if(Camera::getY() > Game::Level.MAP_HEIGHT - Camera::cameraRect.h)
            {
                Camera::setY(Game::Level.MAP_HEIGHT - Camera::cameraRect.h);
            }
        }
        
        //Animation
        void Player::Animate()
        {
            this->sprite.Animate();
            
            //Update Collision Rect
            CollisionRect.w = this->sprite.GetFrameSurface(this->sprite.GetFrame())->w;
            CollisionRect.h = this->sprite.GetFrameSurface(this->sprite.GetFrame())->h;
        }
        
        //Render
        void Player::Render()
        {
            this->sprite.Render(this->x - Camera::getX(), this->y - Camera::getY());
        }
        //Gravity Management
        void Player::Gravity()
        {
            if(Gravity_Enabled)
            {
                //Make player fall
                this->y += this->speed;
                
                //Update Collision Rect
                CollisionRect.x = this->x;
                CollisionRect.y = this->y;
            }
        }
    }
}