#ifndef init_h
#define init_h
#include<SDL/SDL.h>
#include<SDL/SDL_image.h>
#include<SDL/SDL_mixer.h>
struct Image
{
   SDL_Rect rectangle;
   SDL_Rect rectangleinscreen;
   SDL_Surface *image;
   Mix_Music *AM,*PM,*SM;
   int i;
};
typedef struct Image Image;
 
void init_img_back(Image *settings,SDL_Surface *screen);
void afficherbackgroound(Image c,SDL_Surface *screen);






#endif  
