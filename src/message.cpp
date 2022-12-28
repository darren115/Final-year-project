#include <iostream>
#include <fstream>
#include "message.h"


Message::Message(char* filename, string name)
{
    string line;
    ifstream myfile (filename);
    if (myfile.is_open())
    {
        while (! myfile.eof() )
        {
            getline (myfile,line);
            for (int i=0; i<20; i++)
            {
                int found=line.find("Blink", i);
                if (found !=string::npos)
                    line.replace(found, 5, name);
            }
            text.push_back(line);
        }
        myfile.close();
    }

    else cout << "Unable to open file"; 
        
}


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
    msg = SDL_CreateRGBSurface(SDL_HWSURFACE, 400, 150, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);

    SDL_FillRect(msg, NULL, SDL_MapRGB(msg->format, 0, 0, 0));
    
    SDL_Rect srcdest;
    srcdest.x = 1;
    srcdest.y = 1;
    srcdest.w = 398;
    srcdest.h = 148;

    SDL_FillRect(msg, &srcdest, SDL_MapRGB(msg->format, 129, 83, 10));
    
    srcdest.x = 4;
    srcdest.y = 4;
    srcdest.w = 392;
    srcdest.h = 142;

    SDL_FillRect(msg, &srcdest, SDL_MapRGB(msg->format, 0, 0, 0));
    
    for (unsigned int i = 0; i < text.size(); i++)
        font->write(msg,text[i].c_str(),5,(15*i));
    
    return msg;
}

SDL_Surface* Message::DrawMessage(SFont *font, int w, int h)
{
    SDL_Surface* msg;
    msg = SDL_CreateRGBSurface(SDL_HWSURFACE, w, h, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);

    SDL_FillRect(msg, NULL, SDL_MapRGB(msg->format, 0, 0, 0));
    
    SDL_Rect srcdest;
    srcdest.x = 1;
    srcdest.y = 1;
    srcdest.w = w-2;
    srcdest.h = h-2;

    SDL_FillRect(msg, &srcdest, SDL_MapRGB(msg->format, 129, 83, 10));
    
    srcdest.x = 4;
    srcdest.y = 4;
    srcdest.w = w-8;
    srcdest.h = h-8;

    SDL_FillRect(msg, &srcdest, SDL_MapRGB(msg->format, 0, 0, 0));
    
    for (unsigned int i = 0; i < text.size(); i++)
        font->write(msg,text[i].c_str(),5,(15*i));
    
    return msg;
}
