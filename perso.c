#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <stdlib.h>
#include <stdio.h>
#include "perso.h"
void initPerso(Personne *p){
	int i;
	char image[30];
	p->perso[0][1]=IMG_Load("sprite0.png");
	p->perso[0][2]=IMG_Load("lsprite0.png");
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
	p->PosEcran.y=580;
	p->PosEcran.w=0;
	p->PosEcran.h=0;
	p->Direction=1;
	p->sprite=0;
	p->vie=0;
	p->score=0;
	p->vitesse=0; 
	p->acceleration=0;
	p->up=0;
	p->vitesse_saut=30; 
	p->PosEcranRel.x=-50;
	p->PosEcranRel.y=0;
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
		SDL_BlitSurface(p.perso[0][p.Direction],NULL,screen,&p.PosEcran);
	}
}
void movePerso (Personne *p, uint32_t dt){
	
	p->dx=0.5*p->acceleration*dt*dt+p->vitesse*dt;
	if(p->Direction==2){
		p->dx=-1*p->dx;
	}
	p->PosEcran.x=p->PosEcran.x+p->dx;
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
	else if(p->up!=0){
		if(p->sprite<3&&(p->up==1||p->up==3)){
			p->sprite+=1;
		}
		else if(p->sprite<6&&(p->up==2||p->up==4)){
			p->sprite+=1;
		}
	}
	else{
		p->sprite=0;
	}
}
void saut(Personne *p,int dt, int posx_absolu,int posy_absolu){
	if(p->up==1){	
		if(p->PosEcran.y>=posy_absolu-175){
			if(p->vitesse_saut>0){
				p->vitesse_saut-=2.4;
			}
			p->PosEcran.y-=p->vitesse_saut;
			printf("up=%f\n",p->vitesse_saut);
		}
		else{
			p->PosEcran.y=posy_absolu-175;
			p->up=2;
		}
	}
	else if(p->up==2){
		if(p->PosEcran.y<=posy_absolu){
			if(p->vitesse_saut<30){
				p->vitesse_saut+=2.4;
			}
			p->PosEcran.y+=p->vitesse_saut;
			printf("down=%f\n",p->vitesse_saut);
		}
		else{
			p->PosEcran.y=posy_absolu;
			p->up=0;
		}
	}
            if(p->up==3||p->up==4){
		    p->PosEcranRel.x+=5;
	       	    p->vitesse_saut+=10;
		    p->PosEcranRel.y=(-0.06*(p->PosEcranRel.x*p->PosEcranRel.x)+150);
		    if(p->Direction==1){
		    	p->PosEcran.x = posx_absolu + p->vitesse_saut;
		    }
		    else{
		    	p->PosEcran.x = posx_absolu - p->vitesse_saut;
		    }
		    if(p->PosEcran.x>1235){
		    	p->PosEcran.x=1235;
		    }
		    else if(p->PosEcran.x<0){
		    	p->PosEcran.x=0;
		    }
		    p->PosEcran.y = posy_absolu - p->PosEcranRel.y;
		    if(p->PosEcran.y==posy_absolu-150){
		    	p->up=4;
		    }
	  	    if(p->PosEcran.y>posy_absolu){
	  	    	p->PosEcran.y=posy_absolu;
	  	    	p->up=0;
	  	    	p->vitesse_saut=30;
	  	    	p->PosEcranRel.x=-50;
			p->PosEcranRel.y=0;
	  	    }
  	    }
}
void scrolling(SDL_Rect *b,int direction,double pas){
	if(b->x>=241&&b->x<=459	){
		b->x+=pas;
	}
	else{
		if(b->x<=240){
			b->x=241;
		}
		else if(b->x>=460){
			b->x=459;
		}
	}
}
void initmap(map *m){
	m->img=IMG_Load("mini_background.png");
	m->perso=IMG_Load("sonohead.png");
	m->pos_map.x=1000;
	m->pos_map.y=0;
	m->pos_perso.x=1010;
	m->pos_perso.y=143;
}
void afficherminimap(map m,SDL_Surface *screen){
	SDL_BlitSurface(m.img,NULL,screen,&m.pos_map);
	SDL_BlitSurface(m.perso,NULL,screen,&m.pos_perso);
}
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
