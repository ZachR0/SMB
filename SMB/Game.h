#ifndef SMB_Game_h
#define SMB_Game_h

#include "TMXParse.h"
#include "Player.h"

namespace SMB
{
    namespace Game
    {
        //Flag used to stop game loop
        extern bool QUIT;
        
        //Current Level
        extern Levels::TMX::TMXMap Level;
        
        //Main Player (Mario)
        extern Player::Player MainPlayer;
        
        //Game Initialization
        void Init();
        
        //Game Loop
        void Loop();
        
        //Quits the Game Loop - DeInit game stuff, along with garbage collection
        void Quit();
    }
}


#endif
