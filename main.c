#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <stdbool.h>
#include <math.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include "enigme.h"

int main()
{int i;

SDL_Init(SDL_INIT_VIDEO);
SDL_Surface *screen=NULL;
SDL_Surface *back=NULL;
screen=SDL_SetVideoMode (1000,600,32,SDL_HWSURFACE|SDL_DOUBLEBUF);

SDL_Surface *background=NULL;


SDL_WM_SetCaption("ENIGME\t1",NULL);
bool running=true;
enigme e;
e.anim=0;
e=genererEnigme("enigme.txt");

while (running)
{
    afficherEnigme(&e,screen);
  
    resulitionEnigme(&e,screen);
      SDL_Flip(screen);
   

}
SDL_Quit();

}







 
