#include "Game.h"
#include "Events.h"
#include "Rendering.h"
#include "Camera.h"
#include "FPS.h"
#include "Collision.h"

namespace SMB
{
    namespace Game
    {
        //Flag used to stop game loop
        bool QUIT = false;
        
        //Current Level
        Levels::TMX::TMXMap Level;
        
        //Main Player (Mario)
        Player::Player MainPlayer;
        
        //Game Initialization
        void Init()
        {
            //Load first level (World 1-1)
            Level.LoadMap("data/levels/1/1.tmx");
            
            //Camera System Init
            Camera::Init();
            
            //Load Main Player
            MainPlayer.Init("data/sprites/Mario/Mario_Walking.png", "data/sprites/Mario/Mario_Walking.sm");
            MainPlayer.SetCords(20, 20);
            
            //Initialize Collision Detection
            Collision::Init();
            
            //FPS Regulation Init
            FPS::Init(30); //Cap FPS at 30
            
            //Start Game Loop
            Loop();
        }
        
        //Game Loop
        void Loop()
        {
            while(!QUIT)
            {
                //Handle Events
                Events::Handle();
                
                //Was a quit event executed?
                if(QUIT) break;
                
                //Keep Camera Following Player
                MainPlayer.SetCamera();
                
                //Render Level
                Render::SurfaceRender(Level.AllLayers, SDL_GetVideoSurface(), 0, 0, &Camera::cameraRect);
                
                //Render Player
                MainPlayer.Render();
                
                //Animate Player
                MainPlayer.Animate();
                
                //Check Gravity
                MainPlayer.Gravity();
                
                //Update the screen
                if(SDL_Flip(SDL_GetVideoSurface()) == -1)
                {
                    cout << "[Error]: Updating Screen" << endl;
                }
                
                //Clear the screen
                SDL_FillRect(SDL_GetVideoSurface(), NULL, 0x000000);
                
                //Check if FPS needs to be regulated
                FPS::Check();
            }
        }
        
        //Quits the Game Loop - DeInit game stuff, along with garbage collection
        void Quit()
        {
            //Stop Game Loop
            QUIT = true;
            
            //Free SDL surfaces
            SDL_FreeSurface(Level.AllLayers);
        }
    }
}