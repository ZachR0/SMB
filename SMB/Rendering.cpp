#include "Rendering.h"

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

namespace SMB
{
    namespace Render
    {
        //Loads an image(BMP, PNM, XPM, LBM, PCX, GIF, JPEG, TGA or PNG)
        SDL_Surface *LoadImage(string Filename)
        {
            //Initial Loaded Image
            SDL_Surface *initialImg = NULL;
            
            //Optimized version of the initial loaded image
            SDL_Surface *optimizedImg = NULL;
            
            //Make sure a file was passed
            if(Filename.length() > 0)
            {
                //Catch any issues
                try 
                {
                    initialImg = IMG_Load(Filename.c_str());
                } 
                catch (...)
                {
                    //Does the file exist?
                    cout << "[Error]: Problem loading image \"" << Filename << "\" - Does file exist?" << endl;
                    return NULL;
                }
                
                //Make sure the initial image loaded correctly
                if(initialImg != NULL)
                {
                    //Create optimized image
                    optimizedImg = SDL_DisplayFormatAlpha(initialImg);
                    
                    //Free old image
                    SDL_FreeSurface(initialImg);
                }
                else
                {
                    cout << "[Error]: Problem loading image \"" << Filename << "\" - Does file exist, maybe something else?" << endl;
                }
            }
            
            //Return optmized image
            return optimizedImg;
            
        }
        
        //Renders an SDL_Surface
        void SurfaceRender(SDL_Surface *src, SDL_Surface *dest, int x, int y)
        {
            //Temporary rect to hold offsets
            SDL_Rect offset;
            
            //Give offsets to the rect
            offset.x = x;
            offset.y = y;
            
            //Blit the surface
            SDL_BlitSurface(src, NULL, dest, &offset);
        }
        
        //Renders an SDL_Surface with clipping from the src
        void SurfaceRender(SDL_Surface *src, SDL_Surface *dest, int x, int y, SDL_Rect *clip)
        {
            //Temporary rect to hold offsets
            SDL_Rect offset;
            
            //Give offsets to the rect
            offset.x = x;
            offset.y = y;
            
            //Blit the surface
            SDL_BlitSurface(src, clip, dest, &offset);
        }
        
        //Returns a subimage (clipped area) of another SDL_Surface as a SDL_Surface
        SDL_Surface *GetSubImage(SDL_Surface *surf, SDL_Rect* clip)
        {
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
            
            //Create our 32bit surface for blitting
            SDL_Surface *sub = SDL_CreateRGBSurface(SDL_SWSURFACE, clip->w, clip->h, 32, rmask, gmask, bmask, amask);
            
            //Create a copy of our source image to clip from
            SDL_Surface *tmp = SDL_DisplayFormatAlpha(surf);
            
            //Set Alpha accordingly
            SDL_SetAlpha(tmp, 0, 0);
            
            //Blit our clipped tmp surface to sub
            SDL_BlitSurface(tmp, clip, sub, NULL);
            
            //Garbage Collection FTW
            SDL_FreeSurface(tmp);
            
            //Return our subimage
            return sub;
        }
        
        //Geneterates Text to an SDL_Surface
        SDL_Surface *GenerateText(string Text, SDL_Color ForegroundColor, TTF_Font *Font)
        {
            //Surface to render TTF to
            SDL_Surface *TextSurf = NULL;
            
            //Render TTF and make sure all went well
            if ((TextSurf = TTF_RenderText_Solid(Font, Text.c_str(), ForegroundColor)) == NULL)
            {
                cout << "[Error]: There was a problem rendering your text" << endl;
            }
            
            return TextSurf;
        }
        
        
    }
}