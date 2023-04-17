#ifndef FICHIER_H_INCLUDED
#define FICHIER_H_INCLUDED
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>


typedef struct
{
    SDL_Rect pos;
    SDL_Surface *surf;
} Background;


typedef struct
{
    SDL_Rect pos;
    SDL_Surface *img;
}image;



typedef struct Score 
{ 
   int scoreActuel;
   char Nom[10];
   
}Score;



void InitBouton(image *B,char Buttom[],int X,int Y);

void initBack(Background * b);
void afficher(image i, SDL_Surface *ecran);
//il s'agit d'une MAJ des fonctions init afficher background (voir atelier pour plus de detail)										
void scrolrBack (Background * b); //meme principe que animer perso voir atelier animation	
void cleanup(SDL_Surface *IMAGE);
void showTopThreeScores(SDL_Surface *ecran);

					
	
#endif //FICHIER_H_INCLUDED
