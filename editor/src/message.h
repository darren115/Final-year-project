#include <string>
#include <vector>
#include <SDL/SDL.h>
#include "Font.cpp"

using std::string;
using std::vector;

///contains methods fro drawing messages to the screen
class Message
{
    public:
        ///draws a message to the surface with the supplied font, and returns the surface
        SDL_Surface* DrawMessage(SFont *font);
        
        ///constructor that sets the messages data file
        Message(char* filename);
        
    protected:
        ///the text of the message
        vector<string> text;
};
        
