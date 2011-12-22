#ifndef SMB_Rendering_h
#define SMB_Rendering_h

#include <iostream>
#include <string>
#include <SDL/SDL.h>
#include <SDL_image/SDL_image.h>
#include <SDL_ttf/SDL_ttf.h>

using namespace std;

namespace SMB
{
    namespace Render
    {
        //Loads an image(BMP, PNM, XPM, LBM, PCX, GIF, JPEG, TGA or PNG)
        SDL_Surface *LoadImage(string Filename);
        
        //Renders an SDL_Surface
        void SurfaceRender(SDL_Surface *src, SDL_Surface *dest, int x, int y);
        
        //Renders an SDL_Surface with clipping from the src
        void SurfaceRender(SDL_Surface *src, SDL_Surface *dest, int x, int y, SDL_Rect *clip);
        
        //Returns a subimage (clipped area) of another SDL_Surface as a SDL_Surface
        SDL_Surface *GetSubImage(SDL_Surface *surf, SDL_Rect* clip);
        
        //Geneterates Text to an SDL_Surface
        SDL_Surface *GenerateText(string Text, SDL_Color ForegroundColor, TTF_Font *Font);
    }
}

#endif
