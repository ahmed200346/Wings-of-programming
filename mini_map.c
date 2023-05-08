#include <stdio.h>
#include <stdlib.h>
#include<SDL/SDL.h>
#include<SDL/SDL_ttf.h>
#include<SDL/SDL_image.h>
#include<SDL/SDL_mixer.h>
#include "mini_map.h"
/** 
*@file mini_map.c
*@brief Testing program
*@author Ahmed Aziz
*@version 0.1
*@date May 7 2023
*Testing doxygen 
*/
/**
*@brief Load Background du niveau 1
*@param pointeur sur image
*@return rien
*/
void level_1(image *i)
{
	i->image=IMG_Load("level1.png");
	i->pos1.x=0;
	i->pos1.y=0;
}
/**
*@brief Load Background du niveau 2
*@param pointeur sur image
*@return rien
*/
void level_2(image *i)
{
	i->image=IMG_Load("level2.png");
	i->pos1.x=0;
	i->pos1.y=0;
}
/**
*@brief Load Background du niveau 3
*@param pointeur sur image
*@return rien
*/
void level_3(image *i)
{
	i->image=IMG_Load("level3.png");
	i->pos1.x=0;
	i->pos1.y=0;
}
/**
*@brief Load mini_map avec animation du niveau 1 et initialiser sa position avec la position du mini_hero
*@param pointeur sur mini map 
*@return rien
*/
void initmap_level1(mini_map *m)
{
	m->background=IMG_Load("mini_level1.png");
	m->posbackground.x=1000;
	m->posbackground.y=0;
	m->mini_personne=IMG_Load("gab.png");
	m->posmini_perosnne.x=1050;
	m->posmini_perosnne.y=110;
}
/**
*@brief Load mini_map  avec animation du niveau 2 et initialiser sa position avec la position du mini_hero
*@param pointeur sur mini map 
*@return rien
*/
void initmap_level2(mini_map *m)
{
	m->background=IMG_Load("mini_level2.png");
	m->posbackground.x=1000;
	m->posbackground.y=0;
	m->mini_personne=IMG_Load("gab.png");
	m->posmini_perosnne.x=1030;
	m->posmini_perosnne.y=132;
}
/**
*@brief Load mini_map avec animation du niveau 3 et initialiser sa position avec la position du mini_hero
*@param pointeur sur mini map 
*@return rien
*/
void initmap_level3(mini_map *m)
{
	m->background=IMG_Load("mini_level3.png");
	m->posbackground.x=400;
	m->posbackground.y=0;
	m->mini_personne=IMG_Load("gab.png");
	m->posmini_perosnne.x=1030;
	m->posmini_perosnne.y=125;
}
/**
*@brief Affichage du mini_map et du mini_hero 
*@param pointeur sur mini map et surface pour l'afficher sur elle
*@return rien
*/
void afficher (mini_map m, SDL_Surface * screen)
{
	SDL_BlitSurface(m.background,NULL,screen,&m.posbackground);
	SDL_BlitSurface(m.mini_personne,NULL,screen,&m.posmini_perosnne);
}
/**
*@brief Calculer le temps depuis lancement du jeu  et l'afficher 
*@param variable qui possede le temps ecoule,fenetre 
*@return rien
*/
void affichertemps(uint32_t start_time,SDL_Surface *screen)
{
	uint32_t time;
	time=SDL_GetTicks() - start_time;
	SDL_Rect position;
	position.x=720;
	position.y=-20;
	position.w=0;
	position.h=0;
	int seconds,milleseconds,minutes=0;
	seconds=time/1000;
	minutes=seconds/60;
	seconds-=minutes*60;
	milleseconds=time%1000;
	char text[1000];
	TTF_Font *police;
	police=TTF_OpenFont("Pixeled.ttf",25);
	SDL_Color Couleur;
	Couleur.r=100;
	Couleur.g=150;
	Couleur.b=200;
	sprintf(text,"TIME= %u:%u:%02u",minutes,seconds,milleseconds);
	SDL_Surface *surface;
	surface=TTF_RenderText_Solid(police,text,Couleur);
	SDL_BlitSurface(surface,NULL,screen,&position);
	TTF_CloseFont(police);
	SDL_FreeSurface(surface);
}
/**
*@brief Moad animation du niveau 1 
*@param pointeur sur mini_map 
*@return rien
*/
void init_animation1(mini_map* i)
{
	i->nb_img=10;
	FILE* fich;
	fich=fopen("data1.txt","r");
    	i->img_actuelle=0;
    	char nameIMG[30]; 
    //parcoure
    int ip;
   for ( ip = 0; ip < 4; ip++)
    {
    
        fscanf(fich,"%s",nameIMG);
        i->img[ip] = IMG_Load(nameIMG);
    }
i->pos.x=1250;
i->pos.y=0;
fclose(fich);
}
/**
*@brief Moad animation du niveau 2 et niveau 3 
*@param pointeur sur mini_map 
*@return rien
*/
void init_animation2(mini_map* i)
{
	FILE* fich;
	fich=fopen("data2.txt","r");
    	i->img_actuelle=0;
    	char nameIMG[30]; 
    //parcoure
    int ip;
   for ( ip = 0; ip < 4; ip++)
    {
    
        fscanf(fich,"%s",nameIMG);
        i->img[ip] = IMG_Load(nameIMG);
    }
i->pos.x=1200;
i->pos.y=25;
fclose(fich);
}
/**
*@brief Afficher  le sens de fin du chaque  niveau 
*@param pointeur sur mini_map et fenetre pour afficher l'animation
*@return rien
*/
void affiche_animation(mini_map * i,SDL_Surface *screen){
 	SDL_BlitSurface(i->img[i->img_actuelle],NULL,screen,&i->pos);
    	i->img_actuelle++;
    	SDL_Delay(400);
    	if (i->img_actuelle == 4) i->img_actuelle=0;
}
/**
*@brief Load masque du niveau 1
*@param Surface
*@return rien
*/
void initMasquelevel1(SDL_Surface *Masque)
{
	Masque=IMG_Load("/home/aziz/masque_level1.png");
}
/**
*@brief Load masque du niveau 2
*@param Surface
*@return rien
*/
void initMasquelevel2(SDL_Surface *Masque)
{
	Masque=IMG_Load("/home/aziz/masque_level2.png");
}
/**
*@brief Load masque du niveau 3
*@param Surface
*@return rien
*/
void initMasquelevel3(SDL_Surface *Masque)
{
	Masque=IMG_Load("/home/aziz/masque_level23.png");
}
/**
*@brief Detecter si il y'a intersction les cordonnées du surface masqué entre parametre est le point du cordonnées (x,y) par 
*@param Surface et coordonées de reference 
*@return Color du masque du surface 
*/
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
/**
*@brief Detecter si il y'a intersction les cordonnées du surface masqué entre parametre est le point du cordonnées (x,y) par 
*@param Surface et coordonées de reference 
*@return Color du masque du surface 
*/
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
/**
*@brief Liberer mémoire les resources
*@param  pointeur sur mini_map
*@return rien
*/
void Liberer (mini_map  *m)
{
	SDL_FreeSurface(m->background);
	SDL_FreeSurface(m->mini_personne);
	SDL_FreeSurface(m->animation);
}
