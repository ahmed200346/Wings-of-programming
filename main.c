#include "perso.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
int main(){
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Surface *screen,*back;
	SDL_Rect pos;
	Personne p;
	SDL_Event event;
	int done=1,accel=-1,decel=-1,posinit=0,keyup=0;
	uint32_t dt,t_prev;
	back=IMG_Load("BACKGROUND.png");
	pos.x=0;
	pos.y=0;
	initPerso(&p);
	screen=SDL_SetVideoMode(1300,500,32,SDL_HWSURFACE|SDL_DOUBLEBUF);
	while(done==1){
		t_prev=SDL_GetTicks();
		while(SDL_PollEvent(&event)){
			switch(event.type){
			case SDL_KEYDOWN:
				if(event.key.keysym.sym==SDLK_ESCAPE){
					done=0;
				}
				else if(event.key.keysym.sym==SDLK_RIGHT&&p.up==0){
					p.Direction=1;
					p.vitesse=5;
					accel=1;
					decel=0;
				}
				else if(event.key.keysym.sym==SDLK_LEFT&&p.up==0){
					p.Direction=2;
					p.vitesse=5;
					accel=1;
					decel=0;
				}
				else if(event.key.keysym.sym==SDLK_UP&&p.up==0){
					p.up=1;
					p.sprite=0;
				}
				break;
			case SDL_KEYUP:
				if(event.key.keysym.sym==SDLK_LEFT||event.key.keysym.sym==SDLK_RIGHT){
					keyup=1;
					accel=0;
					decel=1;
				}
				break;
			}
		}
		if(accel==1&&p.acceleration<1.36){
			p.acceleration+=0.06;
		}
		if(p.up==0){
			if(decel==1){
				p.acceleration-=0.06;
			}
			if(keyup==1){
				p.vitesse=0;
				keyup=0;
			}
			p.acceleration-=0.01;
		}
		if (p.acceleration<0){
			p.acceleration=0;
		}
		SDL_Delay(3);
		dt=SDL_GetTicks()-t_prev;
		movePerso(&p,dt);
		saut(&p,dt,posinit);
		if(p.up==0){
			posinit=p.PosEcran.y;
		}
		animerPerso(&p);
		SDL_BlitSurface(back,NULL,screen,&pos);
		afficherPerso(p,screen);
		SDL_Flip(screen);
		SDL_Delay(20);
	}
	return 0;
}
