#ifndef SMB_Console_h
#define SMB_Console_h

#include <SDL/SDL.h>
#include <SDL_ttf/SDL_ttf.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

namespace SMB
{
    namespace Console
    {
        //Console SDL Surface
        extern SDL_Surface *Console_Surface;
        
        //Console Text (Each element is a line of text)
        extern vector<string>Console_Text;
        
        //Number of lines that contain data
        extern int Current_Line;
        
        //Console Text Font
        extern TTF_Font *Font;
        
        //Console Active Status
        extern bool Active;
        
        //Initializes Console
        void Init();
        
        //Console Event Handling
        void Events();
        
        //Renders Console to Screen
        void Render();
        
        //Writes text to console
        void Write(string text);
        
        //DeInitalizes Console
        void DeInit();
        
        
    }
}


#endif
