#include <iostream>
#include <fstream>
#include "message.h"


Message::Message(char* filename)
{
    string line;
    ifstream myfile (filename);
    if (myfile.is_open())
    {
        while (! myfile.eof() )
        {
            getline (myfile,line);
            text.push_back(line);
        }
        myfile.close();
    }

    else cout << "Unable to open file"; 
        
}

SDL_Surface* Message::DrawMessage(SFont *font)
{
    SDL_Surface* msg;
    msg = SDL_CreateRGBSurface(SDL_HWSURFACE, 640, 480, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
    
    SDL_SetColorKey(msg, SDL_SRCCOLORKEY, SDL_MapRGB(msg->format, 0, 0, 0));

    SDL_FillRect(msg, NULL, SDL_MapRGB(msg->format, 0, 0, 0));
    
    for (unsigned int i = 0; i < text.size(); i++)
        font->write(msg,text[i].c_str(),(15*i));
    
    return msg;
}

