#include "ennemi.h"
void move_eleph(Enemie *entity , Personne *Hero)
{
if( entity->life > 0)
{
if( entity->TempImage < 1 && entity->NbPas < MAXPAS1 && entity->etat == IDLE)
{	
	if( entity->NbmaxImg !=4 )
		entity->NbmaxImg = 4 ;
	entity->etat = IDLE ; 
	if(entity->direction == LEFT)
	{
		entity->y -=  20 * sin(((entity->x - DebutX_elephant)*3,14) / 24) + entity->dirY;
		entity->x -= SPEED;
	}
	else if (entity->direction == RIGHT)
	{
		entity->y -= 20 * sin(((entity->x - DebutX_elephant)*3,14) / 24) + entity->dirY;
		entity->x += SPEED ;
	}
entity->NbPas ++ ;
if(entity->NbPas == ( MAXPAS1 / 2 ) )
{
	srand(time(NULL));
	entity->dirY = rand()%11 - 5 ; 
}
if(entity->y <= ( DebutY_elephant - 100 ) || entity->y >= ( DebutY_elephant + 200 ))
		entity->dirY -= 2 * entity->dirY ;
}
if( entity->NbPas >= MAXPAS1 ) 
{
	entity->etat = TURN ; 
	if(entity->NbmaxImg != 2)
	{
		entity->NbmaxImg = 2 ;
		entity->NumImage = 0 ; 
		entity->TempImage = 5; 
	}
	if(entity->direction == RIGHT)
	{
	
		if(entity->NumImage >= entity->NbmaxImg - 1 && entity->TempImage < 1)
		{
			entity->direction = LEFT ;
			entity->NbPas = 0 ;
			entity->etat = IDLE ;
		}
	}
	else 
	{
		if(entity->NumImage >= entity->NbmaxImg - 1 && entity->TempImage < 1)
		{
			
			entity->direction = RIGHT ;
			entity->NbPas = 0;
			entity->etat = IDLE ;
		}
	}
}
switch(collisionBB(*entity,*Hero,300,400))
{
	case 1 :
	if(entity->i >= 2)
		entity->i = 0;
	if( entity->direction == RIGHT && collisionBB(*entity , *Hero , 40, 40 ) != 1 )
	{	
		entity->etat = TURN ;
		if(entity->NbmaxImg != 2)
		{
			entity->NbmaxImg = 2 ;
			entity->NumImage = 0 ; 
			entity->TempImage = 5; 
		}
		if(entity->NumImage >= entity->NbmaxImg - 1 && entity->TempImage < 1)
		{
			entity->direction = LEFT ;
			entity->NbPas = 0 ;
			entity->etat = SUIVRE ;
		}
	}
	if(entity->direction == LEFT && entity->etat == SUIVRE && entity->i < 2)
	{
		if( entity->NbmaxImg != 3 )
		{
			entity->NbmaxImg = 3 ;
			entity->NumImage = 0 ; 
			entity->TempImage = 5; 
		}
		if(entity->NumImage >= entity->NbmaxImg - 1 && entity->TempImage < 1)
		{
			entity->i ++;
			if(entity->i >= 2)
				entity->etat = ATTACK ;
		}
	}
	if(entity->etat == ATTACK && entity->direction == LEFT && entity->TempImage < 1) 
	{
		if( entity->NbmaxImg != 6 )
		{
			entity->NbmaxImg = 6 ;
			entity->NumImage = 3 ; 
			entity->TempImage = 5; 
		}
		entity->SFX++;
		if( entity->y >  Hero->PosEcran.y && entity->y < 360 )
			entity->y -= 20 * sin(((entity->x - DebutX_elephant)*3,14) / 24) + SPEED_MAX ;
		if( entity->x >  Hero->PosEcran.x )
			entity->x -= SPEED_MAX ;
	}
	if( Hero->Attack == 1 && collisionBB(*entity , *Hero , 30 , 30 ) == 1)
	{
		entity->y -=  10*SPEED_MAX;
        	entity->x += 10*SPEED_MAX ;
        	entity->life--;
        	entity->SFX=0;
	}
	else if( Hero->Attack != 1 && collisionBB( *entity , *Hero ,  15 , 15 ) == 1 && entity->etat == ATTACK )
	{
        	Hero->PosEcran.x -= 150 ;
        	Hero->vie--;
	}
	break ;
	case 2 :
	if(entity->i >= 2)
		entity->i = 0;
	if(entity->direction == LEFT && collisionBB(*entity , *Hero , 40,40) != 2)
	{
		entity->etat = TURN ;
		if(entity->NbmaxImg != 2)
		{
			entity->NbmaxImg = 2 ;
			entity->NumImage = 0 ; 
			entity->TempImage = 5; 
		}
		if(entity->NumImage >= entity->NbmaxImg - 1 && entity->TempImage < 1)
		{
			entity->direction = RIGHT ;
			entity->NbPas = 0 ;
			entity->etat = SUIVRE ;
		}
	}
	if(entity->direction == RIGHT && entity->etat == SUIVRE && entity->i < 2)
	{
		if( entity->NbmaxImg != 3 )
		{
			entity->NbmaxImg = 3 ;
			entity->NumImage = 0 ; 
			entity->TempImage = 5; 
		}
		if(entity->NumImage >= entity->NbmaxImg - 1 && entity->TempImage < 1)
		{
			entity->i ++;
			if(entity->i >= 2)
				entity->etat = ATTACK ;
		}
	
	}
	if(entity->etat == ATTACK && entity->direction == RIGHT && entity->TempImage < 1 ) 
	{
		if( entity->NbmaxImg != 6 )
		{
			entity->NbmaxImg = 6 ;
			entity->NumImage = 3 ; 
			entity->TempImage = 5; 
		}
		entity->SFX++;
		if( entity->y >  Hero->PosEcran.y  )
			entity->y -= 20 * sin(((entity->x - DebutX_elephant)*3,14) / 24) + SPEED_MAX;
		if( entity->x <  PERSONNE_MAXW + Hero->PosEcran.x )
			entity->x += SPEED_MAX ;
	}
	if( Hero->Attack == 1 && collisionBB(*entity , *Hero , 30 , 30 ) == 2)
	{
		entity->y -=   10*SPEED_MAX ;
        	entity->x -=10*SPEED_MAX ;
        	entity->life--;
        	entity->SFX=0;
	}
	else if( Hero->Attack != 1 && collisionBB( *entity , *Hero , 15 , 15) == 2 && entity->etat == ATTACK )
	{
        	Hero->PosEcran.x -= 150 ;
        	Hero->vie--;
	}
	break ; 
	case 3:
	if(entity->i >= 2)
		entity->i = 0;
	if(entity->direction == RIGHT && collisionBB(*entity , *Hero , 40 , 40 ) != 3)
	{
	
		entity->etat = TURN ;
		if(entity->NbmaxImg != 2)
		{
			entity->NbmaxImg = 2 ;
			entity->NumImage = 0 ; 
			entity->TempImage = 5; 
		}
		if(entity->NumImage >= entity->NbmaxImg - 1 && entity->TempImage < 1 )
		{
			entity->direction = LEFT ;
			entity->NbPas = 0 ;
			entity->etat = SUIVRE ;
		}
	}
	if(entity->direction == LEFT && entity->etat == SUIVRE && entity->i < 2)
	{
		if( entity->NbmaxImg != 3 )
		{
			entity->NbmaxImg = 3 ;
			entity->NumImage = 0 ; 
			entity->TempImage = 5; 
		}
		if(entity->NumImage >= entity->NbmaxImg - 1 && entity->TempImage < 1)
		{
			entity->i ++;
			if(entity->i >= 2)
				entity->etat = ATTACK ;
		}
	
	}
	if(entity->etat == ATTACK && entity->direction == LEFT && entity->TempImage < 1) 
	{
	if( entity->NbmaxImg != 6 )
	{
		entity->NbmaxImg = 6 ;
		entity->NumImage = 3 ; 
		entity->TempImage = 5; 
	}
	entity->SFX++;
	if( entity->y <  Hero->PosEcran.y + PERSONNE_MAXH )
		entity->y += 20 * sin(((entity->x - DebutX_elephant)*3,14) / 24) + SPEED_MAX ;
	if( entity->x >  Hero->PosEcran.x + PERSONNE_MAXW )
		entity->x -= SPEED_MAX ;
	
	}
	if( Hero->Attack == 1 && collisionBB(*entity , *Hero ,  30 , 30 ) == 3)
	{
		entity->y -=   10*SPEED_MAX ;
        	entity->x += 10*SPEED_MAX ;
        	entity->life--;
        	entity->SFX=0;
	}
	else if( Hero->Attack != 1 && collisionBB( *entity , *Hero ,   15 , 15 ) == 3 && entity->etat == ATTACK )
	{
        	Hero->PosEcran.x += 150 ;
        	Hero->vie--;
	}
	break ;
	case 4 :
	if(entity->i >= 2)
		entity->i = 0;
	if(entity->direction == LEFT && collisionBB(*entity , *Hero , 40 , 40 ) != 4)
	{
		entity->etat = TURN ;
		if(entity->NbmaxImg != 2)
		{
			entity->NbmaxImg = 2 ;
			entity->NumImage = 0 ; 
			entity->TempImage = 5; 
		}
		if(entity->NumImage >= entity->NbmaxImg - 1 && entity->TempImage < 1)
		{
			entity->direction = RIGHT ;
			entity->NbPas = 0 ;
			entity->etat = SUIVRE ;
		}
	}
	if(entity->direction == RIGHT && entity->etat == SUIVRE && entity->i < 2)
	{
		if( entity->NbmaxImg != 3 )
		{
			entity->NbmaxImg = 3 ;
			entity->NumImage = 0 ; 
			entity->TempImage = 5; 
		}
		if(entity->NumImage >= entity->NbmaxImg - 1 && entity->TempImage < 1)
		{
			entity->i ++;
			if(entity->i >= 2)
				entity->etat = ATTACK ;
		}
	
	}
	if(entity->etat == ATTACK && entity->direction == RIGHT && entity->TempImage < 1) 
	{
	if( entity->NbmaxImg != 6 )
	{
		entity->NbmaxImg = 6 ;
		entity->NumImage = 3 ; 
		entity->TempImage = 5; 
	}
	entity->SFX++;
	if( entity->y <  Hero->PosEcran.y + PERSONNE_MAXH )
		entity->y += 20 * sin(((entity->x - DebutX_elephant)*3,14) / 24) + SPEED_MAX ;
	if( entity->x <  Hero->PosEcran.x + PERSONNE_MAXW ) 		
		entity->x += SPEED_MAX;
	
	}
	if( Hero->Attack == 1 && collisionBB( *entity , *Hero , 30 , 30) == 4 )
	{
		entity->y -=  10*SPEED_MAX ;
        	entity->x -= 10*SPEED_MAX ;
        	entity->life--;
        	entity->SFX=0;
	}
	else if( Hero->Attack != 1 && collisionBB( *entity , *Hero ,   15 , 15 ) == 4 && entity->etat == ATTACK )
	{
        	Hero->PosEcran.x += 150 ;
        	Hero->vie--;
	}
	break ; 
	case 0 :
		entity->etat = IDLE  ;
		entity->SFX=0;
	break ; 
}
if(entity->y < 450)
	entity->Sur_Terre = 0 ;
else 
	entity->Sur_Terre = 1 ; 
}
if( entity->life <= 0 )
{
	if( entity->Sur_Terre == 0 )
	{
		entity->etat = DEATH_AIR ; 
		if( entity->NbmaxImg != 2 )
		{
			entity->NbmaxImg = 2 ;
			entity->NumImage = 0 ; 
			entity->TempImage = 5;
		}
		if(entity->NumImage >= entity->NbmaxImg - 1 && entity->TempImage < 1 && entity-> Bounce >= 0 )
			entity->y += SPEED_MAX ;
		if( entity->y >= 450 )
		{
			entity->y  = 450  ;
			entity->Sur_Terre = 1 ;
		} 
	}
	else
	{
		if(entity->y >= 450 && entity->Bounce > 0 && entity->NumImage >= entity->NbmaxImg - 1 && entity->TempImage < 1)
		{
			entity->y -= entity-> Bounce * SPEED ;
			entity->x -= SPEED ; 
			entity->Sur_Terre = 0 ;
			entity-> Bounce -- ;
		}
		if(entity->Sur_Terre && entity->Bounce < 1 && entity->etat != EXPLODE && entity->etat != DEATH)
		{	
			entity->etat = DEATH_LAND ;
		}
		if( entity->NbmaxImg != 3 && entity->etat == DEATH_LAND )
		{
			entity->NbmaxImg = 3 ;
			entity->NumImage = 0 ; 
			entity->TempImage = 5; 
			entity->i = 0 ;
		} 
		if( entity->NumImage >= entity->NbmaxImg - 1 && entity->TempImage < 1 )
			entity->i ++ ;
		if( entity->i == 3 && entity->etat != DEATH)
		{
			entity->etat = EXPLODE ; 
			if( entity->NbmaxImg != 13 && entity->etat == EXPLODE)
			{
				entity->NbmaxImg = 13 ;
				entity->NumImage = 0 ; 
				entity->TempImage = 5; 
				entity->SFX=0;
			} 
			entity->SFX++;
		}
		if( entity->NumImage >= entity->NbmaxImg - 1 && entity->TempImage < 1 && entity->etat == EXPLODE)
			{
				entity->etat = DEATH ;
			}
		
		}	
	}
playSoundFx_eleph(*entity);
if(entity->x > Hero->PosEcran.x)
{
	Mix_Volume(-1 ,40*MIX_MAX_VOLUME/(entity->x - Hero->PosEcran.x + 1)); 
}
else
{
	Mix_Volume(-1 ,40*MIX_MAX_VOLUME/(Hero->PosEcran.x - entity->x + 1));	
}			
}
void AfficherEnnemieAnimer_eleph(Enemie *entity,SDL_Surface *screen,int X) 
  {
  if( entity->etat != DEATH )
  {
    if (entity->TempImage <= 0 )
    {
        entity->TempImage = X;

        entity->NumImage++;
        if( entity->NumImage >= entity->NbmaxImg )
            {
            if(entity->etat != ATTACK && entity->etat != DEATH_AIR)
            	entity->NumImage = 0; 
            else if(entity->etat == ATTACK)
            	entity->NumImage =3;
            else
            	entity->NumImage = 1 ;  
            }
    }
    else
        entity->TempImage--;
    
    SDL_Rect dest;
   
    dest.x = entity->x ;
    if( entity->etat != EXPLODE )
    	dest.y = entity->y ;
    else
    	dest.y = entity->y - 20 ;
    dest.w = entity->w;
    dest.h = entity->h;
    int y ; 
    switch(entity->etat)
    	{
    		case IDLE :
    		entity->w = ELEPH_WIDTH;
        	entity->h = ELEPH_HEIGHT;
        	if(entity->direction == LEFT)
        		y = 0 ;
        	else
        		y = 66 ; 
        	break ;
        	case TURN :
        	entity->w = ELEPH_TURN ;
        	entity->h = ELEPH_TURN ;
        	if(entity->direction == LEFT)
        		y = 132 ;
        	else
        		y = 191 ; 
        	break ;	
        	case SUIVRE : 
        	entity->w = 88 ;
        	entity->h = 60 ;
        	if(entity->direction == LEFT)
        		y = 250 ;
        	else
        		y = 310 ; 
        	break ;
        	case ATTACK : 
        	entity->w = 88 ;
        	entity->h = 60 ;
        	if(entity->direction == LEFT)
        		y = 250 ;
        	else
        		y = 310 ; 
        	break ;
        	case DEATH_AIR :
        	entity->w = 70 ;
        	entity->h = 57 ;
        	if(entity->direction == LEFT)
        		y = 370 ;
        	else
        		y = 427 ; 
        	break ;
        	case DEATH_LAND :
        	entity->w = 54 ;
        	entity->h = 45 ;
        	if(entity->direction == LEFT)
        		y = 484 ;
        	else
        		y = 529 ; 
        	break ;
        	case EXPLODE :
        	entity->w = Phw ;
        	entity->h = Phh ;
        	y = 0 ;
        	break ;
    	}
    SDL_Rect src;
    src.x = entity->NumImage * entity->w;
    src.y = y;
    src.w = entity->w;
    src.h = entity->h;
    if(entity->etat != EXPLODE)
    {
   	 SDL_BlitSurface(entity->sprite, &src, screen, &dest);
    }
    else
    {
    	SDL_BlitSurface(entity->P_effects, &src, screen, &dest);
    }
    }
}
void playSoundFx_eleph(Enemie entity)
{
    switch (entity.etat)
    {
        case IDLE:
        	Mix_PlayChannel(-1,entity.Flying, 0 );
        break;
        case SUIVRE:
        	Mix_AllocateChannels(2);    
            	Mix_PlayChannel(-1,entity.Scream, 0);
        break;
        case ATTACK :
        	Mix_AllocateChannels(3); 
        	if(entity.SFX <= 1)         
                	Mix_PlayChannel(-1, entity.Swoop, 0);
        break;
        case EXPLODE:  
        	Mix_AllocateChannels(4);   
        	if(entity.SFX == 15)  
                	Mix_PlayChannel(-1, entity.Explode, 0);
        break;
   }
}
void InitMusics()
{ 
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
	{
	        printf("Mix_OpenAudio: %s\n", Mix_GetError());
	        exit(1);
	}
	    Mix_AllocateChannels(1);
}
void initializeMonster_eleph(Enemie *monster,int x, int y)
{
        monster->sprite = IMG_Load("graph/spritesheet_eleph.png");
        monster->P_effects = IMG_Load("graph/explode_particle.png");
        monster->Scream = Mix_LoadWAV("sounds/scream.wav");
        monster->Flying = Mix_LoadWAV("sounds/flying_loop.wav");
        monster->Swoop = Mix_LoadWAV("sounds/swoop.wav");
        monster->Explode = Mix_LoadWAV("sounds/explode.wav");
        monster->direction = LEFT;
        monster->NbmaxImg = 3 ;
        monster->NumImage = 0;
        monster->TempImage = 30;
        monster->i=0;
        monster->dirY = 0 ;
        monster->x = x;
        monster->y = y;
        monster->Sur_Terre = 0;
        monster->etat = IDLE ;
	monster->NbPas = 0;
	monster->life = 2 ;
	monster->Bounce = 3 ;
	monster->SFX=0;
}
