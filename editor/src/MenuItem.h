#include <string>

using std::string;

///represents an MenuItem in a menu
class MenuItem
{
    public:
        ///indicates whether the MenuItem is selected
        bool selected;    
        
        ///the text displayed for the MenuItem
        string text; 
        
        ///constructor that sets the text of the MenuItem     
        MenuItem (string txt);
};


