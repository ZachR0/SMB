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
            this->jump_count = 0;
            this->Camera_Default = true;
            
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
        
        //Jump
        void Player::Jump()
        {
            //Only allow jumping once
            if(this->jump_count < 1)
            {
                //Enable Gravity
                Gravity_Enabled = true;
                
                //Move player up
                //this->y -= 50;
                
                this->SmoothJump = SDL_CreateThread(jump_move, NULL);
                
                //Update jump count
                this->jump_count++;
                
                /*
                 Note: Jump count gets reset when player gravity is disabled
                 Such as when Player is on the ground, etc
                 */
            }
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
            if(this->Camera_Default)
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
            //Check if gravity is enabled
            if(Gravity_Enabled)
            {
                //Make player fall
                this->y += this->speed*2;
                
                //Update Collision Rect
                CollisionRect.x = this->x;
                CollisionRect.y = this->y;
            }
            else
            {
                //Reset jump count
                this->jump_count = 0;
            }
        }
        
        //Jump movement -- Controls yCord (Allows for smooth jumping)
        int jump_move(void *data)
        {
            int currY = Game::MainPlayer.GetY();
            for(int y = currY; y > currY-90; y--)
            {
                Game::MainPlayer.SetCords(Game::MainPlayer.GetX(), y);
                SDL_Delay(10);
            }
            
            return 0;
        }
    }
}