#include "Console.h"
#include "Rendering.h"
#include "Events.h"

namespace SMB
{
    namespace Console
    {
        //Console SDL Surface
        SDL_Surface *Console_Surface = NULL;
        
        //Console Text (Each element is a line of text)
        vector<string>Console_Text(1);
        
        //Console Input Text
        string Console_Input_Text = "";
        
        //Console Text Font
        TTF_Font *Font = NULL;
        
        //Console Active Status
        bool Active = false;
        
        //Console Size
        const int WIDTH = 319;
        const int HEIGHT = 100;
        
        //Max Console Lines
        const int MAX_LINES = 7;
        
        //Max Line Characters
        const int MAX_CHARS = 62;
        
        //Max Input Characters
        const int MAX_INPUT_CHARS = 60;
        
        //Console Input Line
        const int INPUT_LINE = 7;
        
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
                //Update event state(s)
                SDL_PumpEvents();
                
                
                //Update Object Focus before we call Event function
                if(Events::Event.type == SDL_KEYDOWN)
                {
                    //Key pressed
                    SDLKey key = Events::Event.key.keysym.sym;
                    
                    //Only evaluate certain keys (Letters, numbers, some symbols)
                    if(key == SDLK_a || key == SDLK_b || key == SDLK_c || key == SDLK_d || key == SDLK_e || key == SDLK_f\
                       || key == SDLK_g || key == SDLK_h || key == SDLK_i || key == SDLK_j || key == SDLK_k || key == SDLK_l\
                       || key == SDLK_m || key == SDLK_n || key == SDLK_o || key == SDLK_p || key == SDLK_q || key == SDLK_r\
                       || key == SDLK_s || key == SDLK_t || key == SDLK_u || key == SDLK_v || key == SDLK_w || key == SDLK_x\
                       || key == SDLK_y || key == SDLK_z || key == SDLK_0 || key == SDLK_1 || key == SDLK_2 || key == SDLK_3\
                       || key == SDLK_4 || key == SDLK_5 || key == SDLK_6 || key == SDLK_7 || key == SDLK_8 || key == SDLK_9\
                       || key == SDLK_PERIOD || key == SDLK_SPACE)
                    {
                        Console_Input_Text += key;
                    }
                    
                    //Backspace
                    if(key == SDLK_BACKSPACE)
                    {
                        Console_Input_Text = Console_Input_Text.substr(0, Console_Input_Text.length() - 1);
                    }
                    
                    //Enter - Handle Input
                    if(key == SDLK_RETURN)
                    {
                        //Get copy of input
                        string input = Console_Input_Text;
                        
                        //Reset Console Input
                        Console_Input_Text = "";
                        
                        //Evaluate Input
                        cout << input << endl;
                    }
                }
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
                
                //Render Console Input
                SDL_Surface *data = NULL;
                string input_data = "> ";
                input_data += Console_Input_Text;
                data = Render::GenerateText(input_data, textColor, Font);
                
                //Render to Console
                Render::SurfaceRender(data, Console_Surface, 0, (INPUT_LINE*TTF_FontHeight(Font)));
                
                //GC
                SDL_FreeSurface(data);
                data = NULL;
                
                
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
                if(current_col <= MAX_CHARS)
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