/***************************************************************************
 * Copyright (C) 2005 by David Johnston                                    *
 * dave@windozexp.com                                                      *
 * sound() intialises the sound subsystem				   *
 * initSound sets the audio rate, the type of sound, number of channels and*
 * size of buffer.							   *
 * play music plays music, plain, fade in, or from a posistion		   *
 ***************************************************************************/
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

//Class handling the sound aspects of the game.  It contains methods for initialising the sound 
///subsystem and playing music and effects.  It also contains SDL_mixer functions.
class sound
{
public:
    
    ///Constructor.  When the sound object is created the sound  
    ///subsystem is initialised by calling SDL_Init(SDL_INIT_VIDEO).
    sound();
    
    ///Initialises the sound subsystem.  
    void initSound(int, Uint16, int, int, int);

    ///plays music from a file
    void playMusic(const char *, int, int, double, int); //filename, no_of_times, fade_in, position
    
    ///SDL_mixer function
    int music(const char *, double, int);
    
    ///SDL_mixer function
    int stopMusic(int, int);
    
    ///SDL_mixer function
    void playEffect(const char *, const char *, int, int);
    
    ///SDL_mixer function
    void pauseAll(const char *);
};
