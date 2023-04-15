#ifndef ENNEMI_H
#define ENNEMI_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
//eleph
#define ELEPH_TURN 59
#define ELEPH_HEIGHT 66
#define ELEPH_WIDTH 57
#define DebutX_elephant 600
#define DebutY_elephant 800
#define TURN 5
#define SUIVRE 6
#define DEATH_LAND 7
#define DEATH_AIR 8
#define EXPLODE 9
#define DEATH 10 
#define Phh 86
#define Phw 80
//MONSTER & eleph
#define RIGHT 1
#define LEFT 2
#define ATTACK 3
#define IDLE 4
#define SPEED 4
#define SPEED1 10
#define TIME_BETWEEN_2_FRAMES 24
#define SPEED_MAX 8
#define MAXPAS 10
#define MAXPAS1 30
//MONSTER
#define BEFORE_JUMP 12
#define JUMP 13
#define JUMP_UP 0 
#define JUMP_DOWN 5
#define NILL 1
#define RUN 11
#define STOP 15
#define MONSTER_WIDTH 221
#define MONSTER_HEIGHT 264
#define SPEED_MONSTER 7
#define SPEEDMAX_MONSTER 12
//perso
#define PERSONNE_MAXH 110
#define PERSONNE_MAXW 90

typedef struct
{
	SDL_Rect pos;
	SDL_Surface *img[35];
	int nb_img,img_actuelle;
}image ;

typedef struct Personne{
	SDL_Surface *perso[5][9];
	SDL_Rect PosEcran,PosEcranRel;
	int Direction,vie,score,sprite,up,Attack;
	double vitesse,acceleration,vitesse_saut,dx;
	Mix_Chunk *bref;
}Personne;

typedef struct
{
	SDL_Rect pos,af;
	SDL_Surface *img;
	Mix_Music *song1,*song2,*song3;
	int nbv,enter;
}background;

typedef struct
{
	char *url;
	SDL_Rect pos_map,pos_perso;
	SDL_Surface *img,*perso;
}map;
typedef struct image
{
SDL_Rect Pos;
SDL_Surface *Img;
}Image;
typedef struct Enemie
{
    SDL_Surface *sprite ;
    SDL_Surface *P_effects;
    Mix_Chunk *Scream , *Swoop , *Flying ,*Explode; 
    Mix_Chunk *Walk , *Sword , *Run ,*Prepare ; 
    int x, y;
    int h, w ;
    unsigned int NumImage, TempImage;
    unsigned int etat , direction , etat1, max_jump, NbmaxImg;
    int Saut ;
    int Sur_Terre, Temp_entre2attack;
    int i, dirY;
    unsigned int life, NbPas , Bounce ,SFX;
} Enemie;
void initializeMonster(Enemie *monster,int x, int y);

void AfficherEnnemieAnimer(Enemie *entity,SDL_Surface *screen,int X) ;

void AfficherEnnemie(Enemie e,SDL_Surface *screen);

void move(Enemie *e);

int collisionBB(Enemie Monster , Personne Hero , int x , int y);

void moveIA(Enemie *entity , Personne *Hero );
//ennemi
void cleanupMusic(Mix_Chunk *MUSIC);

void InitMusics();

void playSoundFx_eleph(Enemie entity) ; 

void playSoundFx_monster(Enemie entity) ; 

void AfficherEnnemieAnimer_eleph(Enemie *entity,SDL_Surface *screen,int X) ;

void initializeMonster_eleph(Enemie *monster,int x, int y);

void move_eleph(Enemie *entity , Personne *Hero) ; 

void AfficheImage(Image I , SDL_Surface *IMAGE);
//perso
void init (Personne * p, int numperso);

void initPerso(Personne *p);

void afficherPerso(Personne p, SDL_Surface * screen);

void movePerso (Personne *p, uint32_t dt);

void animerPerso (Personne* p);

void saut(Personne *p,int dt, int posx_absolu,int posy_absolu);

void scrolling(SDL_Rect *b,int direction,double pas);

void initmap(map *m);

void afficherminimap(map m,SDL_Surface *screen);

void affichervie(Personne p,SDL_Surface *screen);

void afficherback(background *b,SDL_Surface *screen);

void affichertemps(uint32_t start_time,SDL_Surface *screen);

void initback(background *b);

//background

void init_image(image * i ,int x , int y );

void affiche (image * i,SDL_Surface*screen);

void liberer(image * i);

void libereperso(Personne p);
#endif
