#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <stdlib.h>
#include <stdio.h>
#include "ennemi.h"
void initPerso(Personne *p){
	int i;
	char image[30];
	p->perso[0][1]=IMG_Load("graph/sprite0.png");
	p->perso[0][2]=IMG_Load("graph/lsprite0.png");
	p->perso[0][3]=IMG_Load("graph/heart.png");
	p->perso[0][4]=IMG_Load("graph/hollowheart.png");
	for(i=1;i<10;i++){
		sprintf(image,"graph/sprite%d.png",i);
		p->perso[1][i-1]=IMG_Load(image);
	}
	for(i=1;i<10;i++){
		sprintf(image,"graph/lsprite%d.png",i);
		p->perso[2][i-1]=IMG_Load(image);
	}
	for(i=1;i<8;i++){
		sprintf(image,"graph/jsprite%d.png",i);
		p->perso[3][i-1]=IMG_Load(image);
	}
	for(i=1;i<8;i++){
		sprintf(image,"graph/ljsprite%d.png",i);
		p->perso[4][i-1]=IMG_Load(image);
	}
	p->PosEcran.x=80;
	p->PosEcran.y=400;
	p->PosEcran.w=0;
	p->PosEcran.h=0;
	p->Direction=1;
	p->sprite=0;
	p->vie=3;
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
	if(b->x>=40&&b->x<=2200){
		b->x+=pas;
	}
	else{
		if(b->x<40){
			b->x=40;
		}
		if(b->x>=2200){
			b->x=2201;
		}
	}
}
void initmap(map *m){
	m->img=IMG_Load("graph/mini_background.png");
	m->perso=IMG_Load("graph/sonohead.png");
	m->pos_map.x=900;
	m->pos_map.y=0;
	m->pos_perso.x=900;
	m->pos_perso.y=27;
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
	position.x=190;
	position.y=-15;
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
void affichervie(Personne p,SDL_Surface *screen){
	SDL_Rect pos;
	pos.x=0;
	pos.y=0;
	switch(p.vie){
	case 3:
		SDL_BlitSurface(p.perso[0][3],NULL,screen,&pos);
		pos.x+=60;
		SDL_BlitSurface(p.perso[0][3],NULL,screen,&pos);
		pos.x+=60;
		SDL_BlitSurface(p.perso[0][3],NULL,screen,&pos);
		break;
	case 2:
		SDL_BlitSurface(p.perso[0][3],NULL,screen,&pos);
		pos.x+=60;
		SDL_BlitSurface(p.perso[0][3],NULL,screen,&pos);
		pos.x+=60;
		SDL_BlitSurface(p.perso[0][4],NULL,screen,&pos);
		break;
	case 1:
		SDL_BlitSurface(p.perso[0][3],NULL,screen,&pos);
		pos.x+=60;
		SDL_BlitSurface(p.perso[0][4],NULL,screen,&pos);
		pos.x+=60;
		SDL_BlitSurface(p.perso[0][4],NULL,screen,&pos);
		break;
	}
}
void afficherback(background *b,SDL_Surface *screen){
	SDL_BlitSurface(b->img,&b->af,screen,&b->pos);
	switch(b->nbv){
	case 2:
		if(b->enter!=1){
			Mix_PlayMusic(b->song2,-1);
			b->enter=1;
		}
		break;
	case 1:
		if(b->enter!=2){
			Mix_PlayMusic(b->song3,-1);
			b->enter=2;
		}
		break;
	case 0:
		Mix_HaltMusic();
		break;
	}
}
void initback(background *b){
	b->img=IMG_Load("graph/BACKGROUND.png");
	b->pos.x=0;
	b->pos.y=0;
	b->af.x=40;
	b->af.y=0;
	b->af.w=2000;
	b->af.h=1080;
	b->song1=Mix_LoadMUS("sounds/1.mp3");
	b->song2=Mix_LoadMUS("sounds/2.mp3");
	b->song3=Mix_LoadMUS("sounds/3.mp3");
	b->enter=0;
}
void libereperso(Personne p){
	int i,j;
	for(i=0;i<5;i++){
		for(j=0;j<9;j++){
			if(p.perso[i][j] != NULL){
				SDL_FreeSurface(p.perso[i][j]);
			}
		}
	}
}
