#include <string>
#include <vector>
#include <SDL/SDL.h>
#include "Font.cpp"

using std::string;
using std::vector;

///Contains methods for drawing messages to the screen.  It loads the message text from a file and 
///has a method to draw the message to a SDL_Surface.  It has a vector containing the lines of the 
///text of the message.
class Message
{
    public:
        ///Draws a message.  It draws a message to a surface with the supplied font, and returns 
        ///the surface for use.
        SDL_Surface* DrawMessage(SFont *font);
        
        SDL_Surface* DrawMessage(SFont *font, int w, int h);
        
        ///Constructor.  It loads the text of the message from the file supplied and saves the lines 
        ///of the message in the string vector text.
        Message(char* filename, string name);
        
        Message(char* filename);
        
    protected:
        ///The text of the message.  Each string in the vector is a line of the message.
        vector<string> text;
};
        
