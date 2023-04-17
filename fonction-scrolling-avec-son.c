#include "header-scrolling-avec-son.h"


void init_img_back(Image *bg,SDL_Surface *screen){
   bg->image=IMG_Load("Final.png");
   if(bg->image==NULL){
printf("loading background img probleme");}
 const SDL_VideoInfo* info = SDL_GetVideoInfo();   

bg->rectangle.x=0;
bg->rectangle.y=0;
 bg->rectangle.h= 1080;
 bg->rectangle.w=info->current_w;

bg->rectangleinscreen.x=0;
bg->rectangleinscreen.y=0;
bg->rectangleinscreen.h=info->current_h ;
bg->rectangleinscreen.w=info->current_w;
bg->i=0;
}
void afficherbackgroound(Image c,SDL_Surface *screen){
 SDL_BlitSurface(c.image,&c.rectangle,screen,&c.rectangleinscreen);


 

//musique
if(c.rectangle.y>850 && (c.rectangle.x>=0 && c.rectangle.x<=1300 )&&c.i!=1 ) 
{
Mix_PlayMusic(c.PM, -1);
c.i=1;
}
else if(c.rectangle.y<850 && (c.rectangle.x>=0 && c.rectangle.x<=1300)&&c.i!=2 )
{
Mix_PlayMusic(c.AM, -1);
c.i=2;
}

else if(c.rectangle.y<850 && (c.rectangle.x>=1300 && c.rectangle.x<=2400)&&c.i!=3 )
{
Mix_PlayMusic(c.SM, -1);
c.i=3;
}



}










