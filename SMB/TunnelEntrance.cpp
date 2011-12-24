#include "TunnelEntrance.h"
#include "Game.h"

namespace SMB 
{
    namespace Levels
    {
        namespace Overlays
        {
            namespace TunnelEntrance
            {
                //Keystate Activation Check Thread
                SDL_Thread *KeystateCheck = NULL;
                bool RUN_CHECK = false;
                
                //Handles Tunnel Entrance Trigger
                void Trigger(string Activate_Direction, string Port_Object)
                {
                    //Disable Player Gravity
                    Game::MainPlayer.Gravity_Enabled = false;
                    
                    //Get Port Location
                    int portX = 0;
                    int portY = 0;
                    
                    //Go through Level Objects
                    for(int i = 0; i < Game::Level.numObjs; i++)
                    {
                        if(Game::Level.Objects[i].name == Port_Object)
                        {
                            //Set Port x,y
                            portX = Game::Level.Objects[i].rect.x;
                            portY = Game::Level.Objects[i].rect.y;
                        }
                    }
                    
                    //Generate Thread Arguments (ActivateDirection;portX;portY)
                    stringstream args;
                    args << Activate_Direction << ";" << portX << ";" << portY;
                    string strargs = args.str();
                    
                    //Start checking keystate
                    RUN_CHECK = true;
                    KeystateCheck = SDL_CreateThread(KeyState_Thread, (void*)strargs.c_str());
                }
                
                //Keystate Activation Check Thread
                int KeyState_Thread(void *data)
                {
                    //Get Argument data
                    string args = (char*)data;
                    string Activate_Direction = args.substr(0,  args.find_first_of(";"));
                    args = args.substr(args.find_first_of(";")+1); //Remove old data
                    
                    string PortX = args.substr(0,  args.find_first_of(";"));
                    args = args.substr(args.find_first_of(";")+1); //Remove old data
                    
                    string PortY = args.substr(0,  args.find_first_of(";"));
                    args = args.substr(args.find_first_of(";")+1); //Remove old data
                    
                    while(RUN_CHECK)
                    {
                        //Check Keystates to see if port should activate
                        if(Activate_Direction == "Down")
                        {
                            Uint8 *keystate = SDL_GetKeyState(NULL);
                            if (keystate[SDLK_DOWN])
                            {
                                //Port Player
                                int x = atoi(PortX.c_str());
                                int y = atoi(PortY.c_str());
                                Game::MainPlayer.SetCords(x, y);
                                
                                //Stop loop
                                break;
                            }
                        }
                        
                        if(Activate_Direction == "Right")
                        {
                            Uint8 *keystate = SDL_GetKeyState(NULL);
                            if (keystate[SDLK_RIGHT])
                            {
                                //Port Player
                                int x = atoi(PortX.c_str());
                                int y = atoi(PortY.c_str());
                                Game::MainPlayer.SetCords(x, y);
                                
                                //Stop loop
                                break;
                            }
                        }
                    }
                    
                    return 0;
                }
                
                //Handles Tunnel Entrance DeTrigger
                void DeTrigger()
                {
                    //Enable Player Gravity
                    Game::MainPlayer.Gravity_Enabled = true;
                    
                    //Stop Keystate checking thread
                    RUN_CHECK = false;
                    SDL_KillThread(KeystateCheck);
                    KeystateCheck = NULL;
                }
            }
        }
    }
}