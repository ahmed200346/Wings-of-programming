#include <stdio.h>
#include <stdlib.h>
#include<SDL/SDL.h>
#include<SDL/SDL_ttf.h>
#include<SDL/SDL_image.h>
#include<SDL/SDL_mixer.h>
#include "mini_map.h"
void level_1(image *i)
{
	i->image=IMG_Load("/home/aziz/level1.png");
	i->pos1.x=0;
	i->pos1.y=0;
}
void level_2(image *i)
{
	i->image=IMG_Load("/home/aziz/level2.png");
	i->pos1.x=0;
	i->pos1.y=0;
}
void level_3(image *i)
{
	i->image=IMG_Load("/home/aziz/level3.png");
	i->pos1.x=0;
	i->pos1.y=0;
}
//1
void initmap_level1(mini_map *m)
{
	m->background=IMG_Load("/home/aziz/mini_level1.png");
	m->posbackground.x=400;
	m->posbackground.y=0;
	m->mini_personne=IMG_Load("/home/aziz/sprite0.png");
	m->posmini_perosnne.x=450;
	m->posmini_perosnne.y=100;
}
void initmap_level2(mini_map *m)
{
	m->background=IMG_Load("/home/aziz/mini_level2.png");
	m->posbackground.x=400;
	m->posbackground.y=0;
	m->mini_personne=IMG_Load("/home/aziz/sprite0.png");
	m->posmini_perosnne.x=450;
	m->posmini_perosnne.y=100;
}
void initmap_level3(mini_map *m)
{
	m->background=IMG_Load("/home/aziz/mini_level3.png");
	m->posbackground.x=400;
	m->posbackground.y=0;
	m->mini_personne=IMG_Load("/home/aziz/sprite0.png");
	m->posmini_perosnne.x=450;
	m->posmini_perosnne.y=100;
}
//2 Afficher mini_map et la version petite du captain  
void afficher (mini_map m, SDL_Surface * screen)
{
	SDL_BlitSurface(m.background,NULL,screen,&m.posbackground);
	SDL_BlitSurface(m.mini_personne,NULL,screen,&m.posmini_perosnne);
}
//4 Afficher temps depuis lancement du jeu et temps restant pour trouver une piece 
void affichertemps(uint32_t start_time,SDL_Surface *screen)
{
	uint32_t time;
	time=SDL_GetTicks() - start_time;
	SDL_Rect position;
	position.x=0;
	position.y=0;
	position.w=0;
	position.h=0;
	int seconds,milleseconds;
	seconds=time/1000;
	milleseconds=time%1000;
	char text[1000];
	TTF_Font *police;
	police=TTF_OpenFont("/home/aziz/futur.ttf",15);
	SDL_Color Couleur;
	Couleur.r=100;
	Couleur.g=150;
	Couleur.b=200;
	sprintf(text,"Temps depuis lancement du jeu est :%u.%03u secondes",seconds,milleseconds);
	SDL_Surface *surface;
	surface=TTF_RenderText_Solid(police,text,Couleur);
	SDL_BlitSurface(surface,NULL,screen,&position);
	TTF_CloseFont(police);
	SDL_FreeSurface(surface);
}
//3 Mise a jour la position du captain dans la map 
void MAJMinimap(SDL_Rect posJoueur,  mini_map * m, SDL_Rect camera, int redimensionnement)
{
	m->posmini_perosnne.x=450+(posJoueur.x/redimensionnement) - m->mini_personne->w;
	m->posmini_perosnne.y=100+(posJoueur.y/redimensionnement) - m->mini_personne->h;
	/*SDL_Rect posJoueurAbsolue;
	posJoueurAbsolue.x=posJoueur.x+camera.x;
	posJoueurAbsolue.y=posJoueur.y+camera.y;	
	m->posmini_perosnne.x=posJoueurAbsolue.x *(redimensionnement/100);
	m->posmini_perosnne.y=posJoueurAbsolue.y *(redimensionnement/100);
	m->posmini_perosnne.w=posJoueurAbsolue.x *(redimensionnement/100);
	m->posmini_perosnne.h=posJoueurAbsolue.x *(redimensionnement/100);*/	
}
//5 Afficher point couloré ou signe d'une piece du spaceship dans le minima
/*void animerMinimap(mini_map *m)
{
	
}*/
void initMasquelevel1(SDL_Surface *Masque)
{
	Masque=IMG_Load("/home/aziz/masque_level1.png");
}
void initMasquelevel2(SDL_Surface *Masque)
{
	Masque=IMG_Load("/home/aziz/masque_level2.png");
}
void initMasquelevel3(SDL_Surface *Masque)
{
	Masque=IMG_Load("/home/aziz/masque_level23.png");
}
int collisionPP(Personne P,SDL_Surface *Masque)
{
	int collision=0,i;
	SDL_Rect pos[8];
	SDL_Color color[8];
	pos[0].x=P.PosEcran.x;
	pos[0].y=P.PosEcran.y;
	pos[1].x=(P.PosEcran.x+P.PosEcran.w)/2;
	pos[1].y=P.PosEcran.y;
	pos[2].x=P.PosEcran.x+P.PosEcran.w;
	pos[2].y=P.PosEcran.y;
	pos[3].x=P.PosEcran.x;
	pos[3].y=(P.PosEcran.y+P.PosEcran.h)/2;
	pos[4].x=P.PosEcran.x;
	pos[4].y=P.PosEcran.y+P.PosEcran.h;
	pos[5].x=(P.PosEcran.x+P.PosEcran.w)/2;
	pos[5].y=P.PosEcran.y+P.PosEcran.h;
	pos[6].x=P.PosEcran.x+P.PosEcran.w;
	pos[6].y=P.PosEcran.y+P.PosEcran.h;
	pos[7].x=P.PosEcran.x+P.PosEcran.w;
	pos[7].y=(P.PosEcran.y+P.PosEcran.h)/2;
	for(i=0;i<8;i++)
	{
		color[i]=GetPixel(Masque,pos[i].x,pos[i].y);
	}
	if((color[4].r==0 && color[4].g==0 && color[4].b==0) && (color[5].r==0 && color[5].b==0 && color[5].g==0) && (color[6].r==0 && 	color[6].g==0 && color[6].b==0)){
		collision=1;}
	return collision;
}
SDL_Color GetPixel(SDL_Surface *pSurface,int x,int y)
{
	SDL_Color color;
	Uint32 col=0;
	char *pPosition=(char*)pSurface->pixels;
	pPosition+=(pSurface->pitch*y);
	pPosition+=(pSurface->format->BytesPerPixel);
	memcpy(&col,pPosition,pSurface->format->BytesPerPixel);
	SDL_GetRGB(col,pSurface->format,&color.r,&color.g,&color.b);
	return color;
}
//6
void Liberer (mini_map  *m)
{
	SDL_FreeSurface(m->background);
	SDL_FreeSurface(m->mini_personne);
}
