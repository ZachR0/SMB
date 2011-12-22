#ifndef SMB_TMXParse_h
#define SMB_TMXParse_h

#include <iostream>
#include <string>
#include <vector>
#include <SDL/SDL.h>

using namespace std;

namespace SMB
{
    namespace Levels
    {
        namespace TMX //Tiled Map Editor
        {
            //Object group objects
            class Object
            {
            public:
                SDL_Rect rect; //Location and size (For collision)
                string name; //Name of object
                string type; //Type of object
                string value; //Data value of object (Normally a script file)
                int trigger_count; //Number of times triggered
                
                //Objecr Init
                Object();
                
                //Called when Object is triggered
                void Trigger();
                
                //Called when Object is detriggered
                void DeTrigger();
            };
            
            class TMXMap
            {
            public:
                SDL_Surface *AllLayers; //All Layers together
                Object *Objects; //Object Group Objects
                int numObjs; //Number of Object Group Objects
                int MAP_WIDTH, MAP_HEIGHT; //Overall Width and Height of Map
                
                //Init
                TMXMap();
                
                //Parses the TMX file and loads all data
                bool LoadMap(string TMXFile);
                
            };
        }
    }
}


#endif
