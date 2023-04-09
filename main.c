#include "perso.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
int main(){
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	SDL_Surface *screen,*back;
	SDL_Rect pos,b;
	Personne p;
	map m;
	SDL_Event event;
	int done=1,accel=-1,decel=-1,posinit=0,keyup=0,posx_absolu,posy_absolu;
	uint32_t dt,t_prev,start_time;
	back=IMG_Load("BACKGROUND.png");
	pos.x=0;
	pos.y=0;
	b.x=250;
	b.y=200;
	b.w=2000;
	b.h=1080;
	start_time=SDL_GetTicks();
	initPerso(&p);
	initmap(&m);
	screen=SDL_SetVideoMode(1300,800,32,SDL_HWSURFACE|SDL_DOUBLEBUF);
	while(done==1){
		t_prev=SDL_GetTicks();
		if(p.up==0){
			posy_absolu=p.PosEcran.y;
			posx_absolu=p.PosEcran.x;
		}
		while(SDL_PollEvent(&event)){
			switch(event.type){
			case SDL_KEYDOWN:
				if(event.key.keysym.sym==SDLK_ESCAPE){
					done=0;
				}
				else if(event.key.keysym.sym==SDLK_RIGHT&&p.up!=3&&p.up!=4){
					p.Direction=1;
					p.vitesse=5;
					accel=1;
					decel=0;
				}
				else if(event.key.keysym.sym==SDLK_LEFT&&p.up!=3&&p.up!=4){
					p.Direction=2;
					p.vitesse=5;
					accel=1;
					decel=0;
				}
				else if(event.key.keysym.sym==SDLK_UP&&p.up==0){
					p.up=1;
					p.sprite=0;
				}
				else if(event.key.keysym.sym==SDLK_j&&p.up==0){
					p.up=3;
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
			if(decel==1){
				p.acceleration-=0.06;
			}
			if(keyup==1){
				p.vitesse=0;
				keyup=0;
			}
			p.acceleration-=0.01;
		if (p.acceleration<0){
			p.acceleration=0;
		}
		SDL_Delay(3);
		dt=SDL_GetTicks()-t_prev;
		movePerso(&p,dt);
		if((p.PosEcran.x>800&&p.Direction==1)||(p.PosEcran.x<150&&p.Direction==2)){
			scrolling(&b,p.Direction,p.dx);
		}
		saut(&p,dt,posx_absolu,posy_absolu);
		animerPerso(&p);
		SDL_BlitSurface(back,&b,screen,&pos);
		afficherPerso(p,screen);
		if(m.pos_perso.x>=1000&&m.pos_perso.x<=1267){
			m.pos_perso.x+=p.dx/4.05;
		}
		else{
			if(m.pos_perso.x<1000){
				m.pos_perso.x=1000;
			}
			else if(m.pos_perso.x>1267){
				m.pos_perso.x=1267;
			}
		}
		m.pos_perso.y=p.PosEcran.y-437;
		afficherminimap(m,screen);
		affichertemps(start_time,screen);
		SDL_Flip(screen);
		SDL_Delay(20);
	}
	return 0;
}
