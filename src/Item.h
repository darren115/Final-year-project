#include "sprite.h"
#include <string>

using std::string;

///Class extending sprite to represent an item.  It adds a String member representing the name 
///of the item.  It also has methods for setting and retrieving the name.
class Item : public sprite
{
    public:
        
        ///Constructor. This sets the name of the item. 
        Item(string n);
        
        ///Sets the name of the item.
        void setName(string n)
        {
            name = n;
        }
        
        ///Returns the name of the item.
        string getName()
        {
            return name;
        }
        
        //Selects the item
        void select(bool val)
        {
             selected=val;
        }
        
        //Returns the selected item
        bool getSelected()
        {
            return selected;
        }
        
        //Sets the items life
        void setIlife(int iL)
        {
             iLife=iL;
        }
        
        //Returns the items life
        int getIlife()
        {
             return iLife;
        }
    
    protected:
        ///The name of the item.
        string name;
        
        //Determines whether the item has been selected
        bool selected;
        
        //Used to determine how long the item has been spawned
        int iLife;
        
};
