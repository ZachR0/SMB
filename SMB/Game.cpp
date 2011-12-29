#include "Game.h"
#include "Events.h"
#include "Rendering.h"
#include "Camera.h"
#include "FPS.h"
#include "Collision.h"
#include "Console.h"

namespace SMB
{
    namespace Game
    {
        //Flag used to stop game loop
        bool QUIT = false;
        
        //Console Debug Output
        bool CONSOLE_DEBUG = true;
        
        //Current Level
        Levels::TMX::TMXMap Level;
        
        //Main Player (Mario)
        Player::Player MainPlayer;
        
        //Game Initialization
        void Init()
        {
            //Console Init
            Console::Init();
            Console::Write("Super Mario Bros Project - Zach Rogers <zachrog@gmail.com>");
            
            //Load first level (World 1-1)
            Level.LoadMap("data/levels/1/1.tmx");
            if(CONSOLE_DEBUG) Console::Write("Loaded World 1-1!");
            
            //Camera System Init
            Camera::Init();
            if(CONSOLE_DEBUG) Console::Write("Initalized Camera System!");
            
            //Load Main Player
            MainPlayer.Init("data/sprites/Mario/Mario_Walking.png", "data/sprites/Mario/Mario_Walking.sm");
            MainPlayer.SetCords(20, 20);
            if(CONSOLE_DEBUG) Console::Write("Main Player Loaded (20, 20)");
            
            //Initialize Collision Detection
            Collision::Init();
            if(CONSOLE_DEBUG) Console::Write("Collision Detection System Initialized!");
            
            //FPS Regulation Init
            FPS::Init(30); //Cap FPS at 30
            if(CONSOLE_DEBUG) Console::Write("FPS Regulated at 30FPS!");
            
            //Start Game Loop
            if(CONSOLE_DEBUG) Console::Write("Entering Game Loop...");
            Loop();
            if(CONSOLE_DEBUG) Console::Write("GAME LOOP EXITED!");
        }
        
        //Game Loop
        void Loop()
        {
            while(!QUIT)
            {
                //Handle Console Events
                Console::Events();
                
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
                
                //Render Console
                Console::Render();
                
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
            if(CONSOLE_DEBUG) Console::Write("Starting Game Quite procedures...");
            
            //Stop Game Loop
            QUIT = true;
            
            //Free SDL surfaces
            SDL_FreeSurface(Level.AllLayers);
        }
    }
}