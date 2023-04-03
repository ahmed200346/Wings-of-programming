#include <stdio.h>
#include <stdlib.h>
#include<SDL/SDL.h>
#include<SDL/SDL_image.h>
#include<SDL/SDL_ttf.h>
#include<SDL/SDL_mixer.h>
#include "mini_map.h"
int main(int argc,char *argv[])
{
	//mini map 
	mini_map M;
	initmap_level2(&M);
	//Time
	uint32_t start_tick,time;
	//Variables
	int arret=0,animation3=0,animation2=0,arret0=0,animation1=0,fullscreen=0,vol=64,arret1=0;
	//vitesse de personne
	int accel=-1,decel=-1;
	uint32_t dt,t_prev;
	//event
	SDL_Event event;
	//images
	image Back,Bounaya,Bounaya3,Bounaya2,Gab,Gab3,Sadek,Gab2,Sadek2,Sadek3,Back3,Back2,Back2_3,Back2_2;
	image re1,re2,re3 ;
	//Audio
	Mix_Music *Music;
	Mix_Chunk *bref;
	//text
	text Text;
	//fenetre
	SDL_Surface *fenetre=NULL;
	// Initialisation Video,Text,Audio;
	TTF_Init();
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	Mix_OpenAudio(22500,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,1024);
	//Parametres de variable text
	Text.pos3.x=0;
	Text.pos3.y=750;
	Text.police=TTF_OpenFont("/home/aziz/futur.ttf",40);
	Text.couleur.r=100;
	Text.couleur.g=150;
	Text.couleur.b=200;
	Text.surface_text=TTF_RenderText_Solid(Text.police,"Wings of programming",Text.couleur);
	//Fenetre
	fenetre=SDL_SetVideoMode(1300,800,32,SDL_HWSURFACE);
	//Music du background
	Music=Mix_LoadMUS("/home/aziz/music_Background.mp3");
	Mix_PlayMusic(Music,-1);
	//button Back
	re1.image=IMG_Load("/home/aziz/back.png");
	re1.pos1.x=500;
	re1.pos1.y=600;
	re1.pos1.w=300;
	re1.pos1.h=200;	
	//Animation n°1 button Back
	re2.image=IMG_Load("/home/aziz/back2.png");
	re2.pos1.x=500;
	re2.pos1.y=600;
	re2.pos1.w=300;
	re2.pos1.h=200;	
	// Animation n°2 button Back
	re3.image=IMG_Load("/home/aziz/back3.png");
	re3.pos1.x=500;
	re3.pos1.y=600;
	re3.pos1.w=300;
	re3.pos1.h=200;	
	//Son bref
	bref=Mix_LoadWAV("/home/aziz/bref.WAV");
	//Background initial
	Back.image=IMG_Load("/home/aziz/background_1.png");
	Back.pos1.x=0;
	Back.pos1.y=0;
	Back.pos1.w=1300;
	Back.pos1.h=800;
	level_1(&Back2);
	level_2(&Back2_2);
	level_3(&Back2_3);
	//Background Options
	Back3.image=IMG_Load("/home/aziz/option.png");
	Back3.pos1.x=0;
	Back3.pos1.y=0;
	Back3.pos1.w=1300;
	Back3.pos1.h=800;
	//Boutton Start
	Bounaya.image=IMG_Load("/home/aziz/play2.png");
	Bounaya.pos1.x=620;
	Bounaya.pos1.y=300;
	Bounaya.pos1.w=300;
	Bounaya.pos1.h=200;
	//Animation n°1 du boutton Start
	Bounaya2.image=IMG_Load("/home/aziz/play3.png");
	Bounaya2.pos1.x=620;
	Bounaya2.pos1.y=300;
	Bounaya2.pos1.w=300;
	Bounaya2.pos1.h=200;
	//Animation n°2 du boutton Start
	Bounaya3.image=IMG_Load("/home/aziz/play.png");
	Bounaya3.pos1.x=620;
	Bounaya3.pos1.y=300;
	Bounaya3.pos1.w=300;
	Bounaya3.pos1.h=200;
	//Boutton Option
	Sadek.image=IMG_Load("/home/aziz/opt.png");
	Sadek.pos1.x=500;
	Sadek.pos1.y=400;
	Sadek.pos1.w=300;
	Sadek.pos1.h=200;
	//Animation n°1 du boutton Options
	Sadek2.image=IMG_Load("/home/aziz/opt3.png");
	Sadek2.pos1.x=500;
	Sadek2.pos1.y=400;
	Sadek2.pos1.w=300;
	Sadek2.pos1.h=200;
	//Animation n°2 du boutton Options
	Sadek3.image=IMG_Load("/home/aziz/opt2.png");
	Sadek3.pos1.x=500;
	Sadek3.pos1.y=400;
	Sadek3.pos1.w=300;
	Sadek3.pos1.h=200;
	//Boutton Exit
	Gab.image=IMG_Load("/home/aziz/qui.png");
	Gab.pos1.x=500;
	Gab.pos1.y=600;
	Gab.pos1.w=300;
	Gab.pos1.h=200;
	//Animation n°1 du boutton Exit
	Gab2.image=IMG_Load("/home/aziz/qui3.png");
	Gab2.pos1.x=500;
	Gab2.pos1.y=600;
	Gab2.pos1.w=300;
	Gab2.pos1.h=200;
	//Animation n°2 du boutton Exit
	Gab3.image=IMG_Load("/home/aziz/qui2.png");
	Gab3.pos1.x=500;
	Gab3.pos1.y=600;
	Gab3.pos1.w=300;
	Gab3.pos1.h=200;
	//boucle du menu
	while(arret==0){		
	if(animation3==1 || animation2==1 || animation1==1)
	{
		if(animation3==1 || animation2==1){
			if(animation3==1){
				Mix_PlayChannel(-1,bref,0);
				SDL_BlitSurface(Back.image,NULL,fenetre,&Back.pos1);
				SDL_BlitSurface(Sadek.image,NULL,fenetre,&Sadek.pos1);
				SDL_BlitSurface(Bounaya.image,NULL,fenetre,&Bounaya.pos1);
				SDL_BlitSurface(Gab2.image,NULL,fenetre,&Gab2.pos1);
				SDL_BlitSurface(Text.surface_text,NULL,fenetre,&Text.pos3);
				SDL_Flip(fenetre);}
			 if(animation2==1){
				Mix_PlayChannel(-1,bref,0);
				SDL_BlitSurface(Back.image,NULL,fenetre,&Back.pos1);
				SDL_BlitSurface(Bounaya.image,NULL,fenetre,&Bounaya.pos1);
				SDL_BlitSurface(Gab.image,NULL,fenetre,&Gab.pos1);
				SDL_BlitSurface(Sadek2.image,NULL,fenetre,&Sadek2.pos1);
				SDL_BlitSurface(Text.surface_text,NULL,fenetre,&Text.pos3);
				SDL_Flip(fenetre);}
		 }
		 if(animation1==1)
		{
			Mix_PlayChannel(-1,bref,0);
			SDL_BlitSurface(Back.image,NULL,fenetre,&Back.pos1);
			SDL_BlitSurface(Gab.image,NULL,fenetre,&Gab.pos1);
			SDL_BlitSurface(Sadek.image,NULL,fenetre,&Sadek2.pos1);
			SDL_BlitSurface(Bounaya2.image,NULL,fenetre,&Bounaya.pos1);
			SDL_BlitSurface(Text.surface_text,NULL,fenetre,&Text.pos3);
			SDL_Flip(fenetre);
		}	
	}
	if(animation1==2 || animation2==2 || animation3==2)
	{
		if(animation3==2 || animation2==2){
			if(animation3==2){
				Mix_PlayChannel(-1,bref,0);
				SDL_BlitSurface(Back.image,NULL,fenetre,&Back.pos1);
				SDL_BlitSurface(Sadek.image,NULL,fenetre,&Sadek.pos1);
				SDL_BlitSurface(Bounaya.image,NULL,fenetre,&Bounaya.pos1);
				SDL_BlitSurface(Gab3.image,NULL,fenetre,&Gab3.pos1);
				SDL_BlitSurface(Text.surface_text,NULL,fenetre,&Text.pos3);
				SDL_Flip(fenetre);
				arret=1;}
			 if(animation2==2){
				Mix_PlayChannel(-1,bref,0);
				SDL_BlitSurface(Back.image,NULL,fenetre,&Back.pos1);
				SDL_BlitSurface(Bounaya.image,NULL,fenetre,&Bounaya.pos1);
				SDL_BlitSurface(Gab.image,NULL,fenetre,&Gab.pos1);
				SDL_BlitSurface(Sadek3.image,NULL,fenetre,&Sadek3.pos1);
				SDL_BlitSurface(Text.surface_text,NULL,fenetre,&Text.pos3);
				SDL_Flip(fenetre);
				while(arret0==0){
					
					SDL_BlitSurface(Back3.image,NULL,fenetre,&Back3.pos1);
					SDL_BlitSurface(re1.image,NULL,fenetre,&re1.pos1);
					SDL_Flip(fenetre);
					while(SDL_PollEvent(&event)){
					switch (event.type)
					{
						case SDL_KEYDOWN:
						switch(event.key.keysym.sym){
							case SDLK_q:
								arret0=1;
							case SDLK_f:
								if(fullscreen==0){
						 		fullscreen=1; 
						 		fenetre=SDL_SetVideoMode(1300,800,32,SDL_HWSURFACE |											SDL_FULLSCREEN );
						 		}
						 	else if(fullscreen==1){
						 		fullscreen=0;
								fenetre=SDL_SetVideoMode(1300,800,32,SDL_HWSURFACE );
								}
						}
						break;
						case SDL_MOUSEMOTION:
							if(event.motion.x>=500 && event.motion.x<=800 && event.motion.y>=600 && event.motion.y<=800){
							SDL_BlitSurface(Back3.image,NULL,fenetre,&Back3.pos1);
							SDL_BlitSurface(re2.image,NULL,fenetre,&re2.pos1);
							SDL_Flip(fenetre);}
							break;
							case SDL_MOUSEBUTTONDOWN:
						 	if(event.motion.x>=500 && event.motion.x<=800 && event.motion.y>=600 && event.motion.y<=800){
							SDL_BlitSurface(Back3.image,NULL,fenetre,&Back3.pos1);
							SDL_BlitSurface(re3.image,NULL,fenetre,&re3.pos1);
							SDL_Flip(fenetre);
							arret0=1;	}
							break;
							
						}
					}
				}
			}
		}
	}
		 if(animation1==2)
		{
			
			start_tick=SDL_GetTicks();
			Mix_PlayChannel(-1,bref,0);
			SDL_BlitSurface(Back.image,NULL,fenetre,&Back.pos1);
			SDL_BlitSurface(Gab.image,NULL,fenetre,&Gab.pos1);
			SDL_BlitSurface(Sadek.image,NULL,fenetre,&Sadek2.pos1);
			SDL_BlitSurface(Bounaya3.image,NULL,fenetre,&Bounaya3.pos1);
			SDL_BlitSurface(Text.surface_text,NULL,fenetre,&Text.pos3);
			SDL_Flip(fenetre);
			while(arret1==0){
				time=calculertemps(start_tick);
				SDL_BlitSurface(Back2_2.image,NULL,fenetre,&Back.pos1);
				afficher (M,fenetre);
				affichertemps(time,fenetre);
				SDL_Flip(fenetre);
				SDL_Delay(20);
				SDL_PollEvent(&event);
				if(event.type==SDL_QUIT)
				{
					arret1=1;
				}		
				if(event.type==SDL_KEYDOWN){
					if(event.key.keysym.sym==SDLK_q){arret1=1;}
					if(event.key.keysym.sym==SDLK_f){
						 	if(fullscreen==0){
						 		fullscreen=1; 
						 		fenetre=SDL_SetVideoMode(1300,800,32,SDL_HWSURFACE |											SDL_FULLSCREEN );
						 		}
						 	else if(fullscreen==1){
						 		fullscreen=0;
								fenetre=SDL_SetVideoMode(1300,800,32,SDL_HWSURFACE );
								}
						}
					
				}
		}
		
	}		
	else
	{
		SDL_BlitSurface(Back.image,NULL,fenetre,&Back.pos1);
		SDL_BlitSurface(Bounaya.image,NULL,fenetre,&Bounaya.pos1);
		SDL_BlitSurface(Gab.image,NULL,fenetre,&Gab.pos1);
		SDL_BlitSurface(Sadek.image,NULL,fenetre,&Sadek.pos1);
		SDL_BlitSurface(Text.surface_text,NULL,fenetre,&Text.pos3);
		SDL_Flip(fenetre);
	}
		while(SDL_PollEvent(&event)){
			animation3=0;
			animation2=0;
			animation1=0;
			Mix_VolumeMusic(vol);
			switch(event.type){
				case SDL_QUIT:
					arret=1;
					break;
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym)
					{
						case SDLK_ESCAPE:
							arret=1;
							break;   
						 case SDLK_f:
						 	if(fullscreen==0){
						 		fullscreen=1; 
						 		fenetre=SDL_SetVideoMode(1300,800,32,SDL_HWSURFACE |										SDL_FULLSCREEN );
						 		}
						 	else if(fullscreen==1){
						 		fullscreen=0;
								fenetre=SDL_SetVideoMode(1300,800,32,SDL_HWSURFACE );
								}
							break;
						case SDLK_KP_PLUS:
							if(vol<124)
								vol=vol+10;
							if(vol==124)
								vol=128;					
							break;
						case SDLK_KP_MINUS:
							if(vol==4)
								vol=0;
							else
								vol=vol-10;
							break;	
					}
				case SDL_MOUSEMOTION:
					//Button Options(Animation 1)
					if(event.motion.x>=500 && event.motion.x<=800 && 					event.motion.y>=400 && event.motion.y<=600){animation2=1;}
					//Button Exit(Animation 1)
					if(event.motion.x>=500 && event.motion.x<=800 && event.motion.y>=600 && event.motion.y<=800){animation3=1;}
					//Button Start(Animation 1)
					if(event.motion.x>=620 && event.motion.x<=920 && event.motion.y>=300 && event.motion.y<=500){animation1=1;}
					break;				
				case SDL_MOUSEBUTTONDOWN:
					//Button Start(Animation 2)
					if(event.motion.x>=620 && event.motion.x<=920 && 					event.motion.y>=300 && event.motion.y<=500){animation1=2;
						arret1=0;}
					//Button options(Animation 2)
					if(event.motion.x>=500 && event.motion.x<=800 && 					event.motion.y>=400 && event.motion.y<=600){
					animation2=2;
					arret0=0;}
					//Button Exit(Animation 2)
					if(event.motion.x>=500 && event.motion.x<=800 && event.motion.y>=600 && event.motion.y<=800){animation3=2;}
					break;						
						
		}
		SDL_Delay(10);
	}
}	
	//Liberer Mémoire
	Liberer(&M);
	SDL_FreeSurface(Text.surface_text);
	TTF_CloseFont(Text.police);
	TTF_Quit();
	Mix_FreeMusic(Music);
	Mix_FreeChunk(bref);
	SDL_FreeSurface(Gab2.image);
	SDL_FreeSurface(Back2_2.image);
	SDL_FreeSurface(Back2_3.image);
	SDL_FreeSurface(Back2.image);
	SDL_FreeSurface(fenetre);
	SDL_FreeSurface(Back2.image);
	SDL_FreeSurface(Gab3.image);
	SDL_FreeSurface(Bounaya3.image);
	SDL_FreeSurface(Sadek3.image);
	SDL_FreeSurface(Sadek2.image);
	SDL_FreeSurface(Bounaya2.image);
	SDL_FreeSurface(Back3.image);
	SDL_FreeSurface(Back.image);
	SDL_FreeSurface(Gab.image);
	SDL_FreeSurface(Sadek.image);
	SDL_FreeSurface(Bounaya.image);
	SDL_Quit;
	return 0;
	
}
