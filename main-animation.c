#include"header-animation.h"
int main (int argc  , char *argv[])
{
image x;
int done=1;
SDL_Surface*screen;
SDL_Event event;
SDL_Init(SDL_INIT_VIDEO);
screen=SDL_SetVideoMode(945,709,32,SDL_HWSURFACE);
init_image(&x);
while(done){
affiche(&x,screen);
SDL_Flip(screen);
SDL_Delay(100);
SDL_PollEvent(&event);
switch(event.type){

case SDL_KEYDOWN:
done=0;
break;
}
}liberer(&x);
SDL_Quit();
return 0;
}
