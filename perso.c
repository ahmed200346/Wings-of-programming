#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <stdlib.h>
#include <stdio.h>
#include "perso.h"
void initPerso(Personne *p){
	int i;
	char image[30];
	p->perso[0][0]=IMG_Load("sprite0.png");
	for(i=1;i<10;i++){
		sprintf(image,"sprite%d.png",i);
		p->perso[1][i-1]=IMG_Load(image);
	}
	for(i=1;i<10;i++){
		sprintf(image,"lsprite%d.png",i);
		p->perso[2][i-1]=IMG_Load(image);
	}
	for(i=1;i<8;i++){
		sprintf(image,"jsprite%d.png",i);
		p->perso[3][i-1]=IMG_Load(image);
	}
	for(i=1;i<8;i++){
		sprintf(image,"ljsprite%d.png",i);
		p->perso[4][i-1]=IMG_Load(image);
	}
	p->PosEcran.x=80;
	p->PosEcran.y=300;
	p->PosEcran.w=0;
	p->PosEcran.h=0;
	p->Direction=0;
	p->sprite=0;
	p->vie=0;
	p->score=0;
	p->vitesse=0; 
	p->acceleration=0;
	p->up=0;
	p->vitesse_saut=30; 
}
void afficherPerso(Personne p, SDL_Surface * screen){
	if(p.vitesse!=0&&p.up==0){	
		SDL_BlitSurface(p.perso[p.Direction][p.sprite],NULL,screen,&p.PosEcran);
	}
	else if(p.up!=0&&p.Direction==1){
		SDL_BlitSurface(p.perso[3][p.sprite],NULL,screen,&p.PosEcran);
	}
	else if(p.up!=0&&p.Direction==2){
		SDL_BlitSurface(p.perso[4][p.sprite],NULL,screen,&p.PosEcran);
	}
	else{
		SDL_BlitSurface(p.perso[0][0],NULL,screen,&p.PosEcran);
	}
}
void movePerso (Personne *p, uint32_t dt){
	double dx;
	dx=0.5*p->acceleration*dt*dt+p->vitesse*dt;
	if(p->Direction==2){
		dx=-1*dx;
	}
	p->PosEcran.x=p->PosEcran.x+dx;
	if(p->PosEcran.x>1235){
		p->PosEcran.x=1235;
	}
	else if(p->PosEcran.x<0){
		p->PosEcran.x=0;
	}
}
void animerPerso (Personne* p){
	if(p->Direction==1&&p->up==0){
		if(p->sprite<8){
			p->sprite+=1;
		}
		else{
			p->sprite=0;
		}
	}
	else if(p->Direction==2&&p->up==0){
		if(p->sprite<8){
			p->sprite+=1;
		}
		else{
			p->sprite=0;
		}
	}
	else if(p->up==1||p->up==2){
		if(p->sprite<3&&p->up==1){
			p->sprite+=1;
		}
		else if(p->sprite<6&&p->up==2){
			p->sprite+=1;
		}
	}
	else{
		p->sprite=0;
	}
}
void saut(Personne *p,int dt, int posinit){
	if(p->up==1){	
		if(p->PosEcran.y>=posinit-200){
			if(p->vitesse_saut>0){
				p->vitesse_saut-=2.15;
			}
			p->PosEcran.y-=p->vitesse_saut;
			printf("up=%f\n",p->vitesse_saut);
		}
		else{
			p->PosEcran.y=posinit-200;
			p->up=2.1;
		}
	}
	else if(p->up==2){
		if(p->PosEcran.y<=posinit){
			if(p->vitesse_saut<30){
				p->vitesse_saut+=2.15;
			}
			p->PosEcran.y+=p->vitesse_saut;
			printf("down=%f\n",p->vitesse_saut);
		}
		else{
			p->PosEcran.y=posinit;
			p->up=0;
		}
	}
}
