#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <iostream>
#include <fstream>

using namespace std;

bool videoSupport()
{
    SDL_Init(SDL_INIT_VIDEO);
    
    const SDL_VideoInfo* pVideoInfo = SDL_GetVideoInfo();
    int hw;
    int blitHw;
    bool hwSupport = false;

    hw = pVideoInfo->hw_available;
    blitHw = pVideoInfo->blit_hw;

    if(hw == 1 && blitHw == 1)
    {
        hwSupport = true;
    }

	SDL_Quit();

    return hwSupport;
}

bool audioSupport()
{
    SDL_Init(SDL_INIT_AUDIO);

    bool hwSupport = false;
    
    int audio_rate = 22050;
    Uint16 audio_format = AUDIO_S16SYS;
    int audio_channels = 2;
    int audio_buffers = 4096;
 
    if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) == 0) 
        hwSupport = true;

	SDL_Quit();

    return hwSupport;
}


int main(int argc, char *argv[])
{
    ofstream outfile;
    
    outfile.open ("data/game.cfg");
    
	if (videoSupport())
		printf("Video..................OK\n");
	else
		printf("Video..................Fail\n");

	if (audioSupport())
	{
	    printf("Audio..................OK\n");
	    outfile << ":audio 1";
    }
	else
	{
        printf("Audio..................Fail\n");
        outfile << ":audio 0";
    }
	    
	outfile.close();
	
	return 0;
          	
}
	
	
