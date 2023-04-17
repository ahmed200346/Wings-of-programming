#ifndef header_H
#define header_H
#include <SDL/SDL.h> 
#include <SDL/SDL_image.h>



typedef struct{
SDL_Rect pos;
SDL_Surface *img[35];
int nb_img,img_actuelle;
}image ;
void init_image(image * i);
void affiche (image * i,SDL_Surface*screen);
void liberer(image * i);
#endif
