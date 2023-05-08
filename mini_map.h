#ifndef FUNCTIONS_H_ 
#define FUNCTIONS_H_  
#include <stdio.h>
#include <stdlib.h>
#include<SDL/SDL.h>
#include<SDL/SDL_image.h>
#include<SDL/SDL_mixer.h>
/** 
*@struct Background
*@brief structure du background du niveaux
*/
typedef struct Image
{
	SDL_Rect pos1;/*!<position du background*/
	SDL_Surface *image;/*!<Surface du background*/
	
}image;
/** 
*@struct text
*@brief structure du text
*/
typedef struct text2
{
	SDL_Rect pos3;
	TTF_Font *police;
	SDL_Surface *surface_text;
	SDL_Color couleur;
} text;
/** 
*@struct mini_map
*@brief structure de minimap
*/
typedef struct mini_map
{
	SDL_Surface *background,*mini_personne,*animation;/*!<Surface du mini_map et du minihero et d'animation*/
	SDL_Rect posmini_perosnne,posbackground;/*!<position du minihero et position du mini map*/
	SDL_Rect pos;/*!<position d'animation*/
	SDL_Surface *img[4];/*!<Tableu d'image*/
	int img_actuelle;/*!<numero d'image actuelle*/
}mini_map;
void level_1(image *i);
void level_2(image *i);
void level_3(image *i);
void initmap_level1(mini_map *m);
void initmap_level2(mini_map *m);
void initmap_level3(mini_map *m);
void afficher (mini_map m, SDL_Surface * screen);
Uint32  calculertemps(Uint32 start_time);
void affichertemps(Uint32 time,SDL_Surface *screen);
void init_animation1(mini_map* i);
void init_animation2(mini_map* i);
void affiche_animation(mini_map * i,SDL_Surface *screen);
void initMasquelevel1(SDL_Surface *Masque);
void initMasquelevel2(SDL_Surface *Masque);
void initMasquelevel3(SDL_Surface *Masque);
SDL_Color GetPixel(SDL_Surface *pSurface,int x,int y);
int collisionPP(Personne P,SDL_Surface *Masque);
void Liberer (mini_map  *m);
#endif 
