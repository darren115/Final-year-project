#ifndef SPRITEBASE_H
#define SPRITEBASE_H

#include <SDL/SDL.h>
#include <vector>
#include <string>

using namespace std;

///contains surfaces to hold all the images required and methods to load them
class spriteBase
{
public:
    
    ///loads images from a list 
    void loadImage(char *filename, int image, int tileCount);
    
    
    ///returns an image
    SDL_Surface* getImage(int image);
private:
        
    vector<SDL_Surface *> theTiles;   
};
#endif //SPRITEBASE_H
