#include "header.h"



int main(int argc, char *argv[])

{
	SDL_Init(SDL_INIT_EVERYTHING);
	
	image i;
	image c;
	image d;
	image animation1,animation2;
	
	
	
		
      //BUTTON 	
	
	int bh=0;
	
	
	
	//

	int done = 1;
	SDL_Surface *ecran;
	SDL_Surface *bg = IMG_Load("level 1.png");
	
	
	
	
	
	
	
	
	
	 
	
	SDL_Rect posbg;
	posbg.x = 0;
	posbg.y = 0;
	posbg.w=1300;
	posbg.h=712;
	int f = 0;
	SDL_Event event;
	TTF_Init();
	InitBouton(&animation1,"bleu.png",300,150);	
	InitBouton(&animation2,"rouge.png",300,150);
	
		  //BUTTON		
		
		//SDL_BlitSurface(c.img, NULL, ecran, &c.pos);
		
		
	
	ecran = SDL_SetVideoMode(1300, 712, 32, SDL_HWSURFACE | SDL_DOUBLEBUF );
	SDL_BlitSurface(bg, NULL, ecran, &posbg);
	afficher(animation2,ecran);
	SDL_Flip(ecran);

 
	

	
	
	 //BUTTON		
	
	

	while (done)
	{
		// afficher

		//SDL_BlitSurface(bg, NULL, ecran, &posbg);
		  //BUTTON		
		
		//SDL_BlitSurface(c.img, NULL, ecran, &c.pos);
		
		//showTopThreeScores(ecran);
		//
		
		
		
		







		while (SDL_PollEvent(&event))
		{//showTopThreeScores(ecran);
                        //BUTTON		
			bh=0;
			//
			switch (event.type)
			{
			
			case SDL_QUIT:
				done = 0;
				break;
                               
                               
                               
                               
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				
				
					
					
					
				case SDLK_f:
					if (f == 0)
					{
						f = 1;
						ecran = SDL_SetVideoMode(1300, 712, 32, SDL_HWSURFACE |SDL_DOUBLEBUF| SDL_FULLSCREEN);
					}
					else if (f == 1)
					{
						f = 0;
						ecran = SDL_SetVideoMode(1300, 712, 32, SDL_HWSURFACE | SDL_DOUBLEBUF  );
					}
					break;
					
				case SDLK_q:
					done=0;
					
					break;
					}
					
			case SDL_MOUSEMOTION:
				if(event.motion.x>=300 && event.motion.x<= 1200 && event.motion.y>=200 && event.motion.y<= 400)
					{
					
						SDL_BlitSurface(bg, NULL, ecran, &posbg);
						afficher(animation1,ecran);
						SDL_Flip(ecran);					
					}
			case SDL_MOUSEBUTTONDOWN:
				if(event.button.button == SDL_BUTTON_LEFT && event.motion.x>=300 && event.motion.x<= 1200 && event.motion.y>=200 && event.motion.y<= 400)
					{
			
					do{
					while (SDL_PollEvent(&event))
					{
						switch (event.type)
						{
						case SDL_KEYDOWN:
						switch (event.key.keysym.sym)
						{	
							case SDLK_q:
								done=0;
					
							break;
					
						}
						
						}
						}
						SDL_BlitSurface(bg, NULL, ecran, &posbg);
						showTopThreeScores(ecran);
						SDL_Flip(ecran);}
						while(done!=0);
				 done=1;
					}
			  	break;
			
					
					
					
			      
					
				}
			}
		}
		 //BUTTON		
		/*if(bh==2){ SDL_BlitSurface(bg, NULL, ecran, &posbg);
		
		SDL_BlitSurface(d.img, NULL, ecran, &d.pos);
		
		
		
		SDL_Flip(ecran);
		
		
		
		}
		else if(bh==0){
		
		SDL_BlitSurface(bg, NULL, ecran, &posbg);
		
		SDL_BlitSurface(c.img, NULL, ecran, &c.pos);
		
		
		SDL_Flip(ecran);
		
		}*/
		///////
		
		//SDL_Flip(ecran);
	
	
	

        cleanup(i.img);
	cleanup(animation1.img);
	SDL_Quit();
	

	return 0;

}
