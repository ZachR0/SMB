#include "Game.h"
#include "Video.h"

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    //Initialize SDL
    if(SMB::SDL::Init(319, 240, 32))
    {
        //Start Game Init
        SMB::Game::Init(); //If all goes well, the game loop should be running
        
        //Since the Game Loop ended, DeInit SDL
        SMB::SDL::DeInit();
    }
    else
    {
        cout << "[Error]: Something went wrong during SDL init!" << endl;
    }

    
    return 0;
}