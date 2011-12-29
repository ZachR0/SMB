#include <iostream>
#include <string>
#include <zlib.h>
#include "TMXParse.h"
#include "base64.h"
#include "Rendering.h"
#include "pugixml.hpp"
#include "Events.h"
#include "Overlays.h"

using namespace std;
using namespace SMB::Levels::TMX::Base64;

namespace SMB
{
    namespace Levels
    {
        namespace TMX //Tiled Map Editor
        {
            /****************************
                    DEBUG FLAG
               SHOWS DEBUG CONSOLE OUT
             ****************************/
            bool _DEBUG = false;
            
            //Init
            TMXMap::TMXMap()
            {
                //Variable Init
                numObjs = 0;
                MAP_WIDTH = 0;
                MAP_HEIGHT = 0;
            }
            
            bool TMXMap::LoadMap(string TMXFile)
            {
                //Variable Declaration
                SDL_Surface **Layers; //Map Layers
                int numLayers = 0; //Total Number of Layers in Map
                SDL_Surface *TileSheet = NULL; //Surface for TileSheet
                int MapGrid_Width = 0;
                int MapGrid_Height = 0;
                int MapWidth = 0;
                int MapHeight = 0;
                string TileSheet_Location = "";
                int TileSheet_Width = 0;
                int TileSheet_Height = 0;
                int TileSheet_TileWidth = 0;
                int TileSheet_TileHeight = 0;
                int TileSheet_Index_Start = 0;
                
                //RBGA Masks
                Uint32 rmask, gmask, bmask, amask;
                
                //SDL interprets each pixel as a 32-bit number, so our masks must depend on the endianness (byte order) of the machine
                #if SDL_BYTEORDER == SDL_BIG_ENDIAN
                rmask = 0xff000000;
                gmask = 0x00ff0000;
                bmask = 0x0000ff00;
                amask = 0x000000ff;
                #else
                rmask = 0x000000ff;
                gmask = 0x0000ff00;
                bmask = 0x00ff0000;
                amask = 0xff000000;
                #endif
                
                //Get Full Path (For loading local map resources [ex. sprites in the same folder as the map, etc])
                string DIR_LOC = "";
                DIR_LOC = TMXFile.substr(0, TMXFile.find_last_of('/') + 1);
                
                //Pugi XML Doc
                pugi::xml_document tmx;
                
                //Attempted to parse map
                pugi::xml_parse_result result = tmx.load_file(TMXFile.c_str());
                
                //Check parse results
                if(result)
                {
                    //Get map node information
                    pugi::xml_node map = tmx.child("map");
                    
                    //Get child nodes
                    pugi::xml_node tileset = map.child("tileset");
                    
                    //Child node to pull tilesheet location
                    pugi::xml_node tileset_imag = tileset.child("image");
                    
                    //Pull Information from nodes
                    MapGrid_Width = atoi(map.attribute("tilewidth").value());
                    MapGrid_Height = atoi(map.attribute("tileheight").value());
                    MapWidth = atoi(map.attribute("width").value());
                    MapHeight = atoi(map.attribute("height").value());
                    TileSheet_TileWidth = atoi(tileset.attribute("tilewidth").value());
                    TileSheet_TileHeight = atoi(tileset.attribute("tileheight").value());
                    TileSheet_Index_Start = atoi(tileset.attribute("firstgid").value());
                    TileSheet_Width = atoi(tileset_imag.attribute("width").value());
                    TileSheet_Height = atoi(tileset_imag.attribute("height").value());
                    TileSheet_Location = tileset_imag.attribute("source").value();
                    
                    //Set Overall Map width and height
                    MAP_WIDTH = MapGrid_Width * MapWidth;
                    MAP_HEIGHT = MapGrid_Height * MapHeight;
                    
                    //Generate Layers Surface
                    AllLayers = SDL_CreateRGBSurface(SDL_SWSURFACE, MAP_WIDTH, MAP_HEIGHT, 32, rmask, gmask, bmask, amask);
                    SDL_SetAlpha(AllLayers, 0, 0);
                    
                    //Setup Colorkeying for AllLayers - Make all blank layer data transparent
                    Uint32 colorkey = SDL_MapRGB(AllLayers->format, 0xFF, 0xFF, 0xFF );
                    SDL_Rect rect;
                    rect.x = 0;
                    rect.y = 0;
                    rect.w = MAP_WIDTH;
                    rect.h = MAP_HEIGHT;
                    SDL_SetColorKey(AllLayers, SDL_SRCCOLORKEY, colorkey);
                    SDL_FillRect(AllLayers, &rect, colorkey);
                    
                    
                    //Load TileSheet into memory
                    TileSheet = Render::LoadImage((string)(DIR_LOC + TileSheet_Location));
                    
                    //Did the tilesheet load okay?
                    if(TileSheet == NULL)
                    {
                        cout << "[Error]: Issue parsing TMX map \"" << TMXFile << "\"" << endl;
                        cout << "\tProblem loading tilesheet \"" << TileSheet_Location << "\"" << endl;
                        return false;
                    }
                    
                    //Get initial layer count
                    for (pugi::xml_node layer = map.child("layer"); layer; layer = layer.next_sibling("layer"))
                    {
                        numLayers++;
                    }
                    
                    if(_DEBUG) cout << "THERE ARE " << numLayers << " LAYERS!" << endl;
                    
                    
                    //Generate Layers array
                    Layers = new SDL_Surface*[numLayers];
                    
                    //Garbage collection before continuing
                    tileset.empty();
                    tileset_imag.empty();
                    
                    //Go through layer by layer
                    int currentLayer = 0; //Layer count
                    pugi::xml_node layer;
                    for (layer = map.child("layer"); layer; layer = layer.next_sibling("layer"))
                    {
                        //Pull basic layer information
                        string name = layer.attribute("name").value(); //Layer Name
                        int width = atoi(layer.attribute("width").value());
                        int height = atoi(layer.attribute("height").value());
                        
                        if(_DEBUG) cout << "Layer " << name << endl;
                        
                        //Create New Layer Surface
                        Layers[currentLayer] = SDL_CreateRGBSurface(SDL_SWSURFACE, (width * TileSheet_TileWidth), (height * TileSheet_TileHeight), 32, rmask, gmask, bmask, amask);
                        
                        //Set Alpha Accordingly
                        SDL_SetAlpha(Layers[currentLayer], 0, 0);
                        
                        //Setup Colorkeying for Layer - Make all blank layer data transparent
                        Uint32 colorkey = SDL_MapRGB(Layers[currentLayer]->format, 0xFF, 0xFF, 0xFF );
                        SDL_Rect rect;
                        rect.x = 0;
                        rect.y = 0;
                        rect.w = (width * TileSheet_TileWidth);
                        rect.h = (height * TileSheet_TileHeight);
                        SDL_SetColorKey(Layers[currentLayer], SDL_SRCCOLORKEY, colorkey);
                        SDL_FillRect(Layers[currentLayer], &rect, colorkey);
                        
                        if(_DEBUG) cout << "\tLayer Surface created (" << (int)currentLayer << "," << name  << ")" << endl;
                        
                        
                        //Get data child node from current layer
                        pugi::xml_node data = layer.child("data");
                        
                        if(_DEBUG) cout << "\tLoading / decoding data...";
                        
                        //Start process of decoding data
                        char* dataToDecode = (char*)data.first_child().value(); //Decode first child
                        const int BUFFER_SIZE = 1048576; //2048 8192
                        unsigned char *decodedData;
                        decodedData = new unsigned char[BUFFER_SIZE];
                        size_t outputLength = base64_decode(dataToDecode, decodedData, BUFFER_SIZE);
                        unsigned long bufferSize = 2097152; //4096 16348
                        Bytef *uncompressedData;
                        uncompressedData = new Bytef[bufferSize];
                        
                        //Uncompress data (zlib)
                        switch(uncompress(uncompressedData, &bufferSize, (Bytef*)decodedData, outputLength))
                        {
                            if(_DEBUG) cout << "\tUncompressing data check...";
                            
                            //ZLIB Uncompress Successful
                            case Z_OK:
                            {
                                if(_DEBUG) cout << " OK " << endl;
                                
                                //Keeps track of tile placement
                                int xRow = 0;
                                int yRow = 0;
                                
                                //Go through each data value decompessed
                                if(_DEBUG) cout << "\tGoing through each data value..." << endl;
                                for(int zlibIDX=0; zlibIDX < bufferSize; zlibIDX += 4)
                                {
                                    //Set current tile data value
                                    int tiledata = *((int*)&uncompressedData[zlibIDX]);
                                    
                                    if(_DEBUG) cout << "\t Processing tiledata \"" << tiledata << "\"" << endl;
                                    
                                    //Skip rendering stuff for blank tiles
                                    if(tiledata >= TileSheet_Index_Start)
                                    {
                                        //Prepare Variables for pulling the tile from the tilesheet
                                        SDL_Rect clip;
                                        clip.x = 1;
                                        clip.y = 1;
                                        clip.w = TileSheet_TileWidth;
                                        clip.h = TileSheet_TileHeight;
                                        
                                        //Locate the correct clip x,y of tile on the tilesheet
                                        bool TileFound = false;
                                        int CurrentTileID = TileSheet_Index_Start;
                                        for (int OffY = 0; OffY < TileSheet_Height; OffY += TileSheet_TileHeight)
                                        {
                                            for (int OffX = 0; OffX < TileSheet_Width; OffX += TileSheet_TileWidth)
                                            {
                                                if (CurrentTileID == tiledata)
                                                {
                                                    clip.x = (OffX);
                                                    clip.y = (OffY);
                                                    
                                                    TileFound = true;
                                                    break;
                                                }
                                                
                                                CurrentTileID++;
                                            }
                                            
                                            if (TileFound)
                                            {
                                                break;
                                            }
                                        }
                                        
                                        if(_DEBUG) cout << "\t\tTile Clip: x(" << clip.x << ") y(" << clip.y << ") w(" << clip.w << ") h(" << clip.h << ")" << endl;
                                        if(_DEBUG) cout << "\t\t\tBlank Tile = " << TileSheet_Index_Start-1 << endl;
                                        
                                        if(_DEBUG) cout << "\t\tRendering tile from tilesheet...";
                                        
                                        //Render tile from tilesheet to correct layer
                                        SDL_Rect dest;
                                        dest.x = xRow * TileSheet_TileWidth;
                                        dest.y = yRow * TileSheet_TileHeight;
                                        SDL_BlitSurface(TileSheet, &clip, Layers[currentLayer], &dest);

                                    }
                                                            
                                    
                                    //Update x and y tile placement
                                    if(xRow < width-1)
                                    {
                                        if(_DEBUG) cout << "\t\tIncreasing xRow (" << xRow << " -> ";
                                        
                                        xRow += 1;
                                        
                                        if(_DEBUG) cout << xRow << ")" << endl;
                                    }
                                    else
                                    {
                                        //Reset x placement
                                        xRow = 0;
                                        
                                        if(_DEBUG) cout << "\t\tReset xRow, increasing yRow (" << yRow << " -> ";
                                        
                                        //Update y placement
                                        yRow += 1;
                                        
                                       if(_DEBUG) cout << yRow << ")" << endl;
                                    }
                                    
                                }
                                
                                break;
                            }
                                
                            //ZLIB Memory Error
                            case Z_MEM_ERROR:
                            {
                                cout << "[Error]: ZLIB - Map Uncompress failed due to MEMORY ERROR" << endl;
                                return false;
                            }
                                
                            //ZLIB Buffer Error
                            case Z_BUF_ERROR:
                            {
                                cout << "[Error]: ZLIB - Map Uncompress failed due to BUFFER ERROR" << endl;
                                return false;
                            }
                                
                            //ZLIB Data Error
                            case Z_DATA_ERROR:
                            {
                                cout << "[Error]: ZLIB - Map Uncompress failed due to DATA ERROR" << endl;
                                return false;
                            }
                        }
                        
                        //Update layer count
                        currentLayer++;
                        
                        //Garbage Collection
                        delete [] decodedData;
                        delete [] uncompressedData;
                    }
                    
                    //Go through each object group to get object count
                    pugi::xml_node objectgroup;
                    for (objectgroup = map.child("objectgroup"); objectgroup; objectgroup = objectgroup.next_sibling("objectgroup"))
                    {
                        //Go through each child object and get an initial count
                        for (pugi::xml_node object = objectgroup.child("object"); object; object = object.next_sibling("object"))
                        {
                            numObjs++;
                        }
                    }
                    
                    
                    //Setup Object class array
                    Objects = new Object[numObjs];
                    
                    //Go through each object group
                    int currentObj = 0;
                    for (objectgroup = map.child("objectgroup"); objectgroup; objectgroup = objectgroup.next_sibling("objectgroup"))
                    {
                        //Go back through each child object and get data
                        for (pugi::xml_node object = objectgroup.child("object"); object; object = object.next_sibling("object"))
                        {
                            //Pull object data
                            Objects[currentObj].name = object.attribute("name").value();
                            Objects[currentObj].type = object.attribute("type").value();
                            //Objects[currentObj].value = object.child("properties").child("property").attribute("value").value();
                            
                            //Pull each object value field and value
                            for (pugi::xml_node objprop = object.child("properties").child("property"); objprop; objprop = objprop.next_sibling("property"))
                            {
                                Objects[currentObj].fieldData.push_back(objprop.attribute("name").value());
                                Objects[currentObj].valueData.push_back(objprop.attribute("value").value());
                            }
                            
                            //Pull object location and size
                            Objects[currentObj].rect.x = atoi(object.attribute("x").value());
                            Objects[currentObj].rect.y = atoi(object.attribute("y").value());
                            Objects[currentObj].rect.w = atoi(object.attribute("width").value());
                            Objects[currentObj].rect.h = atoi(object.attribute("height").value());
                            
                            //Debug output
                            cout << "Object Layer: " << Objects[currentObj].name << " - " << "Type: " << Objects[currentObj].type << " - " << endl;
                            for(int i = 0; i < Objects[currentObj].fieldData.size(); i++)
                            {
                                cout  << "\tValue: " << Objects[currentObj].fieldData[i] << "(" << Objects[currentObj].valueData[i] << ")" << endl;
                            }
                            cout << "\tRect X: " << Objects[currentObj].rect.x << endl << "\tRect Y:" <<  Objects[currentObj].rect.y << endl << \
                            "\tRect W: " << Objects[currentObj].rect.w << endl << "\tRect H:" << Objects[currentObj].rect.h << endl;
                            
                            //Increase counter
                            currentObj++;
                        }
                        
                    }
                    
                    //Draw Layers to AllLayers Surface
                    for(int i = 0; i < numLayers; i++)
                    {
                         //Make sure we can render
                         if(Layers[i] != NULL)
                         {
                             Render::SurfaceRender(Layers[i], AllLayers, 0, 0, NULL);
                         }
                    }
                    
                    
                    //GC
                    map.empty();
                    layer.empty();
                    objectgroup.empty();
                    tmx.empty();
                    
                    //Free Layer surfaces
                    for(int i = 0; i < numLayers; i++)
                    {
                        SDL_FreeSurface(Layers[i]);
                        Layers[i] = NULL;
                    }
                     
                    //Remove Layers array
                    delete [] Layers;
                    
                    //Reset Layers
                    Layers = new SDL_Surface*;
                    Layers = NULL;
                    
                }
                else
                {
                    cout << "[Error]: Failed to parse TMX map \"" << TMXFile << "\"" << endl;
                    return false;
                }
                
                //Further Garbage Collection
                SDL_FreeSurface(TileSheet);
                TileSheet = NULL;
                
                //Assuming all went well
                return true;
            }
            
            //Objecr Init
            Object::Object()
            {
                trigger_count = 0;
            }
            
            //Called when Object is triggered
            void Object::Trigger()
            {
                //Camera Overlay
                if(type == "Camera")
                {
                    //Trigger
                    Overlays::Camera::Trigger(this->rect);
                    
                    //Note: Continuous Trigger needed
                    //To constantly update new camera settings
                    
                    //Update Trigger Count
                    trigger_count++;
                }
                
                //Ground Overlay
                if(type == "Ground")
                {
                    //Check required data values
                    for(int i = 0; i < this->fieldData.size(); i++)
                    {
                        //Check for Collision
                        if(this->fieldData[i] == "Collision")
                        {
                            //Check Collision value (Enabled?)
                            if(this->valueData[i] == "true")
                            {
                                //Trigger
                                Overlays::Ground::Trigger();
                                
                                //Update Trigger Count
                                trigger_count++;
                            }
                        }
                    }
                }
                
                //Platform Overlay
                if(type == "Platform")
                {
                    //Trigger
                    Overlays::Platform::Trigger();
                    
                    //Update Trigger Count
                    trigger_count++;
                }
                
                /***************
                //Overlays that need trigger checking
                ***************/
                //Only allow triggering once
                if(trigger_count == 0)
                {
                    //Check Object Type
                    
                    
                    //Collision Overlay
                    if(type == "Collision")
                    {
                        //Check required data values
                        for(int i = 0; i < this->fieldData.size(); i++)
                        {
                            //Check for Collision
                            if(this->fieldData[i] == "Collision")
                            {
                                //Check Collision value (Enabled?)
                                if(this->valueData[i] == "true")
                                {
                                    //Trigger
                                    Overlays::Collision::Trigger();
                                    
                                    //Update Trigger Count
                                    trigger_count++;
                                }
                            }
                        }
                    }
                    
                    //Tunnel Entrance Overlay
                    if(type == "TunnelEntrance")
                    {
                        //Activation Direction
                        string activate_dir = "";
                        
                        //Port Object Name
                        string port_obj = "";
                        
                        //Check required data values
                        for(int i = 0; i < this->fieldData.size(); i++)
                        {
                            //Get Activation Direction
                            if(this->fieldData[i] == "Activation_Direction")
                            {
                                activate_dir = this->valueData[i];
                            }
                            
                            //Port Object Name
                            if(this->fieldData[i] == "Port")
                            {
                                port_obj = this->valueData[i];
                            }
                        }
                        
                        //Handle Trigger
                        Overlays::TunnelEntrance::Trigger(activate_dir, port_obj);
                        
                        //Update Trigger Count
                        trigger_count++;
                    }
                    
                }
            }
            
            //Called when Object is detriggered
            void Object::DeTrigger()
            {
                //Only DeTrigger if we have already triggered
                if(trigger_count > 0)
                {
                    //Check Object Type
                    
                    //Ground Overlay
                    if(type == "Ground")
                    {
                        //Check required data values
                        for(int i = 0; i < this->fieldData.size(); i++)
                        {
                            //Check for Collision
                            if(this->fieldData[i] == "Collision")
                            {
                                //Check Collision value (Enabled?)
                                if(this->valueData[i] == "true")
                                {
                                    //DeTrigger
                                    Overlays::Ground::DeTrigger();
                                }
                            }
                        }
                    }
                    
                    //Platform Overlay
                    if(type == "Platform")
                    {
                        //DeTrigger
                        Overlays::Platform::DeTrigger();
                    }
                    
                    //Collision Overlay
                    if(type == "Collision")
                    {
                        //Check required data values
                        for(int i = 0; i < this->fieldData.size(); i++)
                        {
                            //Check for Collision
                            if(this->fieldData[i] == "Collision")
                            {
                                //Check Collision value (Enabled?)
                                if(this->valueData[i] == "true")
                                {
                                    //DeTrigger
                                    Overlays::Collision::Trigger();
                                }
                            }
                        }
                    }
                    
                    //Tunnel Entrance Overlay
                    if(type == "TunnelEntrance")
                    {
                        //DeTrigger
                        Overlays::TunnelEntrance::DeTrigger();
                    }
                    
                    //Camera Overlay
                    if(type == "Camera")
                    {
                        //DeTrigger
                        Overlays::Camera::DeTrigger();
                    }
                    
                    //Reset trigger count
                    trigger_count = 0;
                }
                
            }
        }
    }
}