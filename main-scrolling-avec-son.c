#include "header-scrolling-avec-son.h"
#include<SDL/SDL_mixer.h>
int main()
{

    int boucle = 1;
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Surface *screen,*bg;
    SDL_Rect pos;
    bg=IMG_Load("black.jpeg");
    pos.x=0;
    pos.y=0;
    screen = SDL_SetVideoMode(1920, 1080, 32, SDL_HWSURFACE | SDL_RESIZABLE|SDL_DOUBLEBUF);
    Image back;
    init_img_back(&back, screen);
    afficherbackgroound(back, screen);
    SDL_Event event;
    Mix_OpenAudio(22500,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,1024);
    back.AM=Mix_LoadMUS("1.mp3");
    back.PM=Mix_LoadMUS("2.mp3");
    back.SM=Mix_LoadMUS("3.mp3");

    while (boucle == 1)
    {
        SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
        boucle = 0;
        break;
case SDL_KEYDOWN:

switch (event.key.keysym.sym)
{
case SDLK_RIGHT :
if( back.rectangle.x<=5300){
  back.rectangle.x= back.rectangle.x+20;
  }
break;
 case SDLK_LEFT :
 if( back.rectangle.x>=150){
  back.rectangle.x=back.rectangle.x-15;
}
break;

case SDLK_DOWN :
 {
  back.rectangle.y=back.rectangle.y+15;
}
break;

case SDLK_UP:
 {
  back.rectangle.y=back.rectangle.y-15;
}
break;
   default:
   break;
}


break;
    default:
        break;
    }
     SDL_BlitSurface(bg,NULL,screen,&pos);
     afficherbackgroound(back,screen);
     SDL_Flip(screen);
}
SDL_FreeSurface(screen);
}
