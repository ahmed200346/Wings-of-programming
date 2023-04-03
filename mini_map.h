#ifndef FUNCTIONS_H_ 
#define FUNCTIONS_H_  
#include <stdio.h>
#include <stdlib.h>
#include<SDL/SDL.h>
#include<SDL/SDL_image.h>
#include<SDL/SDL_mixer.h>
typedef struct Image
{
	SDL_Rect pos1;
	SDL_Surface *image;
}image;
typedef struct text2
{
	SDL_Rect pos3;
	TTF_Font *police;
	SDL_Surface *surface_text;
	SDL_Color couleur;
} text;
typedef struct mini_map
{
	SDL_Surface *background,*mini_personne;
	SDL_Rect posmini_perosnne,posbackground;
}mini_map;
typedef struct Personne{
	SDL_Surface *perso[3][9];
	SDL_Rect PosEcran;
	int Direction,vie,score,vitesse_saut,sprite;
	double vitesse, acceleration;
	Mix_Chunk *bref;
}Personne;
//Mini_map
void level_1(image *i);
void level_2(image *i);
void level_3(image *i);
void initmap_level1(mini_map *m);
void initmap_level2(mini_map *m);
void initmap_level3(mini_map *m);
void afficher (mini_map m, SDL_Surface * screen);
Uint32  calculertemps(Uint32 start_time);
void affichertemps(Uint32 time,SDL_Surface *screen);
void MAJMinimap(SDL_Rect posJoueur,  mini_map * m, SDL_Rect camera, int redimensionnement);
void animerMinimap(mini_map *m);
void initMasque(SDL_Surface *Masque);
int collisionPP(Personne P,SDL_Surface *Masque);
void Liberer (mini_map  *m);
//Personne
void initPerso(Personne *p);
void afficherPerso(Personne p, SDL_Surface * screen);
void movePerso (Personne *p, uint32_t dt);
void animerPerso (Personne* p);
void saut (Personne* p);
#endif 
