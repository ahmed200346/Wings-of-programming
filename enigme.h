#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <time.h>

typedef struct enigme
{
    SDL_Surface *background;
    SDL_Surface *anim_bg[10];
    char question[50],rep1[15],rep2[15],rep3[15];
    int solution,ans,anim;
     SDL_Surface *correct;
     SDL_Surface *wrong;
     SDL_Surface *time;
     
}enigme;   





enigme genererEnigme(char *fichier);
void afficherEnigme(enigme *e, SDL_Surface * screen);
void resulitionEnigme(enigme *e ,SDL_Surface *screen);
