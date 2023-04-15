#include "ennemi.h"
int main(){
	SDL_Init(SDL_INIT_EVERYTHING);
	InitMusics();
	TTF_Init();
	SDL_Surface *screen,*back ;
	image Etoile ;
	SDL_Rect pos;
	Personne p;
	Enemie Monster , Monster1 ;
	map m;
	background b ;
	SDL_Event event;
	int done=1,accel=-1,decel=-1,posinit=0,keyup=0,posx_absolu,posy_absolu;
	uint32_t dt,t_prev,start_time;
	start_time=SDL_GetTicks();
	init_image(&Etoile , 200 , 50 );
	initPerso(&p);
	b.nbv=p.vie;
	initback(&b);
	initializeMonster(&Monster1,2500,250);
	initializeMonster_eleph(&Monster,1000,200);
	initmap(&m);
	Mix_PlayMusic(b.song1,-1);
	screen=SDL_SetVideoMode(1300,600,32,SDL_HWSURFACE|SDL_DOUBLEBUF);
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
				else if( event.key.keysym.sym==SDLK_h )
				{
					p.Attack = 1 ;
				}
				break;
			case SDL_KEYUP:
				if(event.key.keysym.sym==SDLK_LEFT||event.key.keysym.sym==SDLK_RIGHT){
					keyup=1;
					accel=0;
					decel=1;
				}
				else if( event.key.keysym.sym==SDLK_h )
				{
					p.Attack = 0 ;
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
		if(((p.PosEcran.x>800&&p.Direction==1)||(p.PosEcran.x<150&&p.Direction==2))&&p.vitesse!=0){
			scrolling(&b.af,p.Direction,p.dx);
			Monster.x-=p.dx;
			Monster1.x-=p.dx;
			}
		if(accel==1){
			movePerso(&p,dt);
			if(p.Direction==1){
				m.pos_perso.x+=p.dx/7.4;
			}
			else{
				m.pos_perso.x+=p.dx/10.5;
			}
		}
		saut(&p,dt,posx_absolu,posy_absolu);
		animerPerso(&p);
		b.nbv=p.vie;
		afficherback(&b,screen);
		affichervie(p,screen);
		AfficherEnnemieAnimer_eleph( &Monster,screen , 5 );
		move_eleph(&Monster,&p);
		affiche(&Etoile , screen );
		AfficherEnnemieAnimer( &Monster1 , screen , 5 );
		move( &Monster1 );
		moveIA( &Monster1 , &p );
		afficherPerso(p,screen);
		if(m.pos_perso.x<900){
			m.pos_perso.x=900;
		}
		else if(m.pos_perso.x>1267){
			m.pos_perso.x=1267;
		}
		m.pos_perso.y=(p.PosEcran.y-350)/2;
		afficherminimap(m,screen);
		affichertemps(start_time,screen);
		SDL_Flip(screen);
		SDL_Delay(20);
	}
	SDL_FreeSurface(Monster.sprite);
	cleanupMusic(Monster.Flying);
	cleanupMusic(Monster.Swoop);
	cleanupMusic(Monster.Scream);
	cleanupMusic(Monster.Explode);
	cleanupMusic(Monster1.Walk);
	cleanupMusic(Monster1.Prepare);
	cleanupMusic(Monster1.Sword);
	cleanupMusic(Monster1.Run);
	liberer(&Etoile);
	//libereperso(p);
	return 0;
}
