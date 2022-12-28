/**************************************************************************
* Copyright (C) 2005 by David Johnston                                    *
* dave@windozexp.com                                                      *
*                                                                         *
***************************************************************************/
#include "sound.h"
#include "string.h"

//
//This is the constructor.
//It intialises the sound subsystem.
//
sound::sound()
{
    if (SDL_Init(SDL_INIT_AUDIO) < 0)
    {
        printf("Unable to init SDL: %s\n", SDL_GetError());
        exit(1);
    }
}

//
//Open Audio Device
//
void sound::initSound(int audio_rate, Uint16 audio_format, int audio_channels, int audio_buffers, int noChannels)
{
    if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers))
    {
        printf("Unable to open audio! \n%s\n", SDL_GetError());
        exit(1);
    }

    int query = (Mix_QuerySpec(&audio_rate, &audio_format, &audio_channels));
    if(query == 0)
    {
        printf("There was a problem initialising sound \n%s\n", SDL_GetError());
    }
    
    Mix_AllocateChannels(noChannels);
}

//
//Play Music
//Input: the music file, the number of times to repeat, time to fade in, posistion to play from, playmode
//There is three playmodes, play music (0), fade in (1) and play from a posistion (2).
//Not all modes are available depending on file type (see SDL Documentation)
//repeat -1 is infinte, 1 = one, 2 = two etc
//fadeIn and posistion depend on the file type, typically fadeIn is in milliseconds and position is seconds (mp3 and ogg)
//
void sound::playMusic(const char *filename, int repeat, int fadeIn, double position, int playmode)
{
    Mix_Music *bgMusic = Mix_LoadMUS(filename);
    if(bgMusic == NULL)
    {
        printf("There was a problem loading %s %s\n", filename, SDL_GetError());
    }

    if(playmode == 0)
    {
        if(Mix_PlayMusic(bgMusic, repeat) < 0)
        {
            printf("There was a problem playing the background music %s %s\n", bgMusic, SDL_GetError());
        }
    }
    else if(playmode == 1)
    {
        if(Mix_FadeInMusic(bgMusic, repeat, fadeIn) < 0)
        {
            printf("There was a problem fading in the background music %s %s\n", bgMusic, SDL_GetError());
        }
    }
    else if (playmode == 2)
    {
        if(Mix_FadeInMusicPos(bgMusic, repeat, fadeIn, position) < 0)
        {
            printf("There was a problem playing the backgroud music from a posistion %s %s\n", bgMusic, SDL_GetError());
        }
    }
}

//These are all SDL_mixer functions.
int sound::music(const char *option, double position, int volume)
{

    if(strcmp(option, "pause") == 0)
    {
        Mix_PauseMusic();
    }
    else if(strcmp(option, "resume") == 0)
    {
        Mix_ResumeMusic();
    }
    else if(strcmp(option, "rewind") == 0)
    {
        Mix_RewindMusic();
    }
    else if(strcmp(option, "setpos") == 0)
    {
        Mix_SetMusicPosition(position);
    }
    else if(strcmp(option, "setVolume") == 0)
    {
        Mix_VolumeMusic(volume);
    }
    else if(strcmp(option, "getVolume") == 0)
    {
        int oldVolume = Mix_VolumeMusic(-1);
        return oldVolume;
    }
    
    
    
}

int sound::stopMusic(int stopMode, int fadeOut)
{
    if(stopMode == 0)
    {
        if(Mix_HaltMusic() < 0)
        {
            printf("Error Stopping Music %s", SDL_GetError());
            return -1;
        }
    }
    if(stopMode == 1)
    {
        if(Mix_FadeOutMusic(fadeOut) < 0)
        {
            printf("Error Fading Out Music %s", SDL_GetError());
            return -1;
        }
    }

    return 0;
}

void sound::playEffect(const char *filename, const char *option, int loops, int time)
{
    Mix_Chunk *effect = Mix_LoadWAV(filename);
    int check;
    if(effect == NULL)
    {
        printf("Error loading sound effect %s", SDL_GetError());
    }
    if(strcmp(option, "play") == 0)
    {
        check = Mix_PlayChannel(-1, effect, 0);

    }
    else if(strcmp(option, "playForTime") == 0)
    {
        check = Mix_PlayChannelTimed(-1, effect, loops, time);
    }
    else if(strcmp(option, "fadeIn") == 0)
    {
        check = Mix_FadeInChannel(-1, effect, loops, time);
    }

    if(check < 0)
    {
        printf("Error Playing Sound Effect %s", SDL_GetError());
    }


    //Mix_FreeChunk(effect);
}

void sound::pauseAll(const char *option)
{
    if(strcmp(option, "pause") == 0)
    {
        Mix_Pause(-1);
        Mix_PauseMusic();
    }
    else if(strcmp(option, "resume") == 0)
    {
        Mix_Resume(-1);
        Mix_ResumeMusic();
    }
}

