#include "Console.h"
#include "Rendering.h"

namespace SMB
{
    namespace Console
    {
        //Console SDL Surface
        SDL_Surface *Console_Surface = NULL;
        
        //Console Text (Each element is a line of text)
        vector<string>Console_Text(1);
        
        //Console Text Font
        TTF_Font *Font = NULL;
        
        //Console Active Status
        bool Active = false;
        
        //Console Size
        const int WIDTH = 319;
        const int HEIGHT = 100;
        
        //Max Console Lines
        const int MAX_LINES = 8;
        
        //Initializes Console
        void Init()
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
            
            //Generate Console Surface
            Console_Surface = SDL_CreateRGBSurface(SDL_SWSURFACE, WIDTH, HEIGHT, 32, rmask, gmask, bmask, amask);
            SDL_SetAlpha(Console_Surface, 0, 0);
            
            //Fill Console Surface Background
            SDL_Rect rect;
            rect.x = 0;
            rect.y = 0;
            rect.w = WIDTH;
            rect.h = HEIGHT;
            SDL_FillRect(Console_Surface, &rect, SDL_MapRGBA(Console_Surface->format, 0, 0, 0, 125));
            
            //Load Font
            Font = TTF_OpenFont("data/fonts/Console.ttf", 9);
        }
        
        //Console Event Handling
        void Events()
        {
            //Only if Console is Active
            if(Active)
            {
                
            }
        }
        
        //Renders Console to Screen
        void Render()
        {
            //Only if Console is Active
            if(Active)
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
                
                //Generate Console Surface
                Console_Surface = SDL_CreateRGBSurface(SDL_SWSURFACE, WIDTH, HEIGHT, 32, rmask, gmask, bmask, amask);
                SDL_SetAlpha(Console_Surface, SDL_SRCALPHA, 125);
                
                //Fill Console Surface Background
                SDL_Rect rect;
                rect.x = 0;
                rect.y = 0;
                rect.w = WIDTH;
                rect.h = HEIGHT;
                SDL_FillRect(Console_Surface, &rect, SDL_MapRGBA(Console_Surface->format, 0, 0, 0, 125));
                
                //Text Color
                SDL_Color textColor = {255, 255, 255};
                
                //Generate Text data line by line
                for(int i = 0; i < Console_Text.size()-1; i++) //We use Console_Text.size()-1 because an extra blank buffer is always added after the last line of text
                {
                    //Generate
                    SDL_Surface *data = NULL;
                    data = Render::GenerateText(Console_Text[i], textColor, Font);
                    
                    //Render to Console
                    Render::SurfaceRender(data, Console_Surface, 0, (i*TTF_FontHeight(Font)));
                    
                    //GC
                    SDL_FreeSurface(data);
                    data = NULL;
                }
                
                //Render Console to Screen
                Render::SurfaceRender(Console_Surface, SDL_GetVideoSurface(), 0, 0);
            }
        }
        
        //Writes text to console
        void Write(string text)
        {
            //Check if old data should be removed
            if( (Console_Text.size()) > MAX_LINES) //More than MAX_LINES lines of text
            {
                //Remove the oldest line
                Console_Text.erase(Console_Text.begin());
            }
            
            //Go through each character of text and build up the line data
            int current_col = 0;
            int current_line = Console_Text.size();
            for(int i = 0; i < text.length(); i++)
            {
                //Get character
                string ch = text.substr(i, 1);
                
                //Keep line limit in mind
                if(current_col <= 62)
                {
                    //Add Character to the current line
                    Console_Text[current_line-1] += ch;
                }
                else
                {
                    //Reset current_col
                    current_col = 0;
                    
                    //Reset current_line
                    current_line++;
                    
                    //Add remaining character to next line
                    if(ch == " ")
                    {
                        //No need to start a new line with a space
                        Console_Text.push_back("");
                    }
                    else
                    {
                        Console_Text.push_back(ch);
                    }
                }
                
                //Update col
                current_col++;
            }
            
            //Generate next line buffer
            Console_Text.push_back("");
            
            
            /*//Output Console_Text for Debug purposes
            for(int i = 0; i < Console_Text.size(); i++)
            {
                cout << Console_Text[i] << endl;
            }*/
        }
        
        //DeInitalizes Console
        void DeInit()
        {
            //Deactive Console and Clear Surface
            Active = false;
            SDL_FreeSurface(Console_Surface);
            Console_Surface = NULL;
        }
        
        
    }
}