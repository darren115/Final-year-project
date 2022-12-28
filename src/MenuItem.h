#include <string>

using std::string;

///Represents a MenuItem in a Menu.  Has members for the text displayed for the MenuItem, and a 
///boolean representing whether the MenuItem is selected or not.
class MenuItem
{
    public:
        ///Indicates whether the MenuItem is selected.  Is set to ttrue when the MenuItem is selected
        bool selected;    
        
        ///The text of the MenuItem.  This is the text that is displayed when drawing the Menu.
        string text; 
        
        ///Constructor. It sets the text of the MenuItem and sets selected to false.    
        MenuItem (string txt);
};


