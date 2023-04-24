#include "enigme.h"

enigme genererEnigme(char *fichier){
    FILE* f;
    enigme e;
    srand( time( NULL ) );
    int alea = rand() % 4,p=0;
    e.background=IMG_Load("back.jpg");
    f=fopen(fichier,"r");
    while (p<alea)
    {
        if (fgetc(f)=='\n')
        {
            p++;
        }
        
    }    
    fscanf(f,"%s %s %s %s %d\n",e.question,e.rep1,e.rep2,e.rep3,&e.solution);
    fclose(f);
    e.anim=-1;
   
e.correct=IMG_Load("win.png");

e.wrong=IMG_Load("lose.png");

e.time=IMG_Load("time.png");


    return e;
    
}

void afficherEnigme(enigme *e, SDL_Surface * screen)
{int i;
char d[30];
for(i=0;i<9;i++)
    {
    sprintf(d,"c%d.png",i);
    e->anim_bg[i]=IMG_Load(d);
    }
    SDL_Surface  *quest = NULL ,*rep1 = NULL ,*rep2 = NULL , *rep3 = NULL;
    SDL_Rect posQ,pos1,pos2,pos3;
    TTF_Font *police = NULL;
    SDL_Color couleur = {255,255,255} ;    
    TTF_Init();
    police = TTF_OpenFont("font.ttf", 35);
    quest = TTF_RenderText_Blended(police, e->question, couleur);
    rep1 = TTF_RenderText_Blended(police, e->rep1, couleur);
    rep2 = TTF_RenderText_Blended(police, e->rep2, couleur);
    rep3 = TTF_RenderText_Blended(police, e->rep3, couleur);
    posQ.x=150;
    posQ.y=270;
    pos1.x=170;
    pos1.y=324;
    pos2.x=170;
    pos2.y=410;
    pos3.x=170;
    pos3.y=480;
    SDL_Rect posean;
posean.x=100;
posean.y=20;
SDL_Rect pose;
pose.x=200;
pose.y=150;

SDL_Rect poset;
poset.x=0;
poset.y=0;

   SDL_BlitSurface(e->background, NULL, screen, NULL); 
    SDL_BlitSurface(quest, NULL, screen, &posQ); 
    SDL_BlitSurface(rep1, NULL, screen, &pos1); 
    SDL_BlitSurface(rep2, NULL, screen, &pos2); 
    SDL_BlitSurface(rep3, NULL, screen, &pos3); 
     if (e->anim<=8 && e->ans!=1 && e->ans!=0)
    {	e->anim++;}
    SDL_BlitSurface(e->anim_bg[e->anim],NULL,screen,&posean);
		if (e->anim>=0 && e->anim<8 && e->ans!=1 && e->ans!=0)
		{	SDL_Delay(700);}
	if(e->ans==1 && e->anim<8)
        {  
                    SDL_BlitSurface(e->correct,NULL,screen,&pose);
                    SDL_Delay(1000);
                    }
       else if (e->ans==0 && e->anim<8)
       {
         
                    SDL_BlitSurface(e->wrong,NULL,screen,&pose);
                    SDL_Delay(1000);
        }
    
	if (e->anim==8 && e->ans!=1 && e->ans!=0 ){
	
			SDL_BlitSurface(e->time,NULL,screen,&poset);
			SDL_Delay(1000);
			}

}
void resulitionEnigme(enigme *e ,SDL_Surface *screen)
{ SDL_Event event;

      while(SDL_PollEvent(&event))
	{

       
	switch (event.key.keysym.sym)
	{
	 case SDL_KEYDOWN:	
	{case SDLK_a :
			if (e->solution==1 && e->anim<8)
                {e->ans=1;
                  
                }
                else {e->ans=0;
                  
                }
                
      		break;
            case SDLK_z :
                if (e->solution==2 && e->anim<8)
                {
                   e->ans=1;
                }
                else {
                  e->ans=0;
                }
            break;
            case SDLK_e:
                if (e->solution==3 && e->anim<8)
                {
                    e->ans=1;
                }
                else {
                   e->ans=0;
                }
            break;
            }}
        break;
        }
     
        
  
}



