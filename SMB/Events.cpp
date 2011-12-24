#include "Events.h"
#include "Game.h"
#include "Camera.h"

namespace SMB
{
    namespace Events
    {
        //SDL Event Structure
        SDL_Event Event;
        
        //Event handling lock (For GUI stuff)
        bool EVENT_LOCK = false;
         
        //Handles all supported event input
        void Handle()
        {
            //Loop while there are SDL events to handle
            while(SDL_PollEvent(&Event))
            {
                //SDL Quit (User closed game)
                if(Event.type == SDL_QUIT)
                {
                    //Quit Game
                    Game::Quit();
                }
                
                //Keydown Events
                if(Event.type == SDL_KEYDOWN)
                {
                    //Key pressed
                    SDLKey key = Event.key.keysym.sym;
                    
                    //Escape Key
                    if(key == SDLK_ESCAPE)
                    {
                        //Quit Game
                        Game::Quit();
                    }
                    
                    /*//Camera Movement Testing
                    if(key == SDLK_UP) Camera::setY(Camera::getY() - 5);
                    if(key == SDLK_DOWN) Camera::setY(Camera::getY() + 5);
                    if(key == SDLK_RIGHT) Camera::setX(Camera::getX() + 5);
                    if(key == SDLK_LEFT) Camera::setX(Camera::getX() - 5);*/
                    
                    //Player Movement
                    if(key == SDLK_UP) Game::MainPlayer.Jump();
                    if(key == SDLK_RIGHT) Game::MainPlayer.MoveRight();
                    if(key == SDLK_LEFT) Game::MainPlayer.MoveLeft();
                    
                }
                
                //Keyup Events
                if(Event.type == SDL_KEYUP)
                {
                    //Key released
                    SDLKey key = Event.key.keysym.sym;
                    
                    //Player Movement
                    if(key == SDLK_RIGHT || key == SDLK_LEFT) Game::MainPlayer.MoveStop();
                }
                
            }
            
            
            
        }
        
        
    }
}