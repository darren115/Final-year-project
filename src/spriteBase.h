#ifndef SPRITEBASE_H

#define SPRITEBASE_H

#include <SDL/SDL.h>
#include <vector>

using std::vector;

///contains surfaces to hold all the images required and methods to load them
class spriteBase
{
public:

    
    ///loads images from a list and sets the colorkey transparency     
    void loadPlayerImage(char *filename, int r, int g, int b);
    
    ///loads images from a list and sets the colorkey transparency 
    void loadImage(char *filename, char *image, int r, int g, int b);
    
    ///returns an image
    SDL_Surface* getImage(char *image);
    
    //returns an image using the index
    SDL_Surface* getImage2(int index);
    
private:
    ///left image
    SDL_Surface *leftImage;
    
    ///right image
    SDL_Surface *rightImage;
    
    ///up image
    SDL_Surface *upImage;
    
    ///down image
    SDL_Surface *downImage;
    
    ///second left image
    SDL_Surface *left1Image;
    
    ///second right image
    SDL_Surface *right1Image;
    
    ///second up image
    SDL_Surface *up1Image;
    
    ///second down image
    SDL_Surface *down1Image;
    
    ///second left image
    SDL_Surface *left2Image;
    
    ///second right image
    SDL_Surface *right2Image;
    
    ///second up image
    SDL_Surface *up2Image;
    
    ///second down image
    SDL_Surface *down2Image;
    
    //vector containing all images
    vector <SDL_Surface *> allImage;
};
#endif //SPRITEBASE_H
