#include "ennemi.h"
void initializeMonster(Enemie *monster,int x, int y)
{
        monster->sprite = IMG_Load("graph/spritesheet_Sentry.png");
        monster->Walk =  Mix_LoadWAV("sounds/Walk.wav");
        monster->Sword =  Mix_LoadWAV("sounds/Sword.wav");
        monster->Run =  Mix_LoadWAV("sounds/Run.wav");
        monster->Prepare =  Mix_LoadWAV("sounds/Prepare.wav");
        monster->direction = LEFT;
        monster->NumImage = 0;
        monster->TempImage = 3;
        monster->x = x;
        monster->y = y;
        monster->w = 122;
        monster->h = MONSTER_HEIGHT;
        monster->Sur_Terre = 1;
	monster->NbPas=0;
	monster->etat = IDLE;
	monster->life = 2 ;
	monster->NbmaxImg = 8 ; 
	monster->i = 0 ; 
	monster->SFX = 0 ;
}
void AfficherEnnemieAnimer(Enemie *entity,SDL_Surface *screen,int X) 
  {
  if(entity->etat != DEATH )
  {
    if (entity->TempImage <= 0)
    {
        entity->TempImage = X;

        entity->NumImage++;

        if( entity->NumImage >= entity->NbmaxImg )
        {
        	entity->NumImage = 0; 
        }
    }
    else
        entity->TempImage--;
    int y ;
    switch(entity->etat)
    	{
    		case IDLE :
    		entity->w = MONSTER_WIDTH;
        	entity->h = MONSTER_HEIGHT;
        	if(entity->direction == LEFT)
        		y = 0 ;
        	else
        		y = 264 ; 
        	break ;
        	case TURN :
        	entity->w = 196 ;
        	entity->h = 223 ;
        	if(entity->direction == LEFT)
        		y = 528 ;
        	else
        		y = 751 ; 
        	break ;	
        	case BEFORE_JUMP :
        	entity->w = 231 ;
        	entity->h = 240 ;
        	if(entity->direction == LEFT)
        		y = 3258 ;
        	else
        		y = 3498 ; 
        	break ;	
        	case JUMP :
        	entity->w = 191 ;
        	entity->h = 239 ;
        	if(entity->direction == LEFT)
        		y = 3738 ;
        	else
        		y = 3977 ; 
        	break ;	
        	case SUIVRE : 
        	entity->w = 215 ;
        	entity->h = 257 ;
        	if(entity->direction == LEFT)
        		y = 974 ;
        	else
        		y = 1231 ; 
        	break ;	
        	case STOP :
        	entity->w = 314 ;
        	entity->h = 278 ;
        	if(entity->direction == LEFT)
        		y = 5120 ;
        	else
        		y = 5398 ; 
        	break ;	
        	case RUN :
        	entity->w = 261;
        	entity->h = 242;
        	if(entity->direction == LEFT)
        		y = 1488 ;
        	else
        		y = 1730 ; 
        	break ;
        	case ATTACK : 
        	entity->w = 371;
        	entity->h = 321;
        	if(entity->direction == LEFT)
        		y = 1972 ;
        	else
        		y = 2293 ; 
        	break ;
        	case DEATH_AIR :
        	entity->w = 160 ;
        	entity->h = 170 ;
        	if( entity->direction == LEFT )
        		y = 5676 ;
        	else
        		y =  5846;
        	break ;
        	case DEATH_LAND :
        	entity->w = 152 ;
        	entity->h = 162 ;
        	if( entity->direction == LEFT )
        		y = 6016 ;
        	else
        		y = 6178;
        	break ; 
    	}
    SDL_Rect dest;
    dest.x = entity->x ;
    if(entity->etat != ATTACK && entity->etat != TURN && entity->etat != DEATH_LAND && entity->etat != DEATH_AIR )
    	dest.y = entity->y ;
    else if(entity->etat == ATTACK)
    	dest.y = entity->y - 50;
    else if(entity->etat == TURN )
    	dest.y = entity->y + 50;
    else
    	dest.y = entity->y + 100;
    dest.w = entity->w;
    dest.h = entity->h;
    SDL_Rect src;
    src.x = entity->NumImage * entity->w ;
    src.y = y;
    src.w = entity->w;
    src.h = entity->h;
    
    SDL_BlitSurface(entity->sprite, &src, screen, &dest);
    }
}
void move( Enemie *entity )
{
	if( (entity->NumImage >= entity->NbmaxImg - 1 || entity->NumImage == 2 || entity->NumImage == 5 ) && entity->TempImage < 1 && entity->NbPas < MAXPAS && entity->etat == IDLE)
	{
		if( entity->NbmaxImg != 8 )
		{
			entity->NbmaxImg = 8 ; 
			entity->NumImage = 0 ;
			entity->TempImage = 3 ;
		}
		if(entity->direction == LEFT)
			entity->x -= SPEED_MONSTER ;
		else
			entity->x += SPEED_MONSTER ;
		entity->NbPas ++ ;
	}
	if(entity->NbPas >= MAXPAS)
	{
		entity->etat = TURN ; 
		if( entity->NbmaxImg != 2 )
		{
			entity->NbmaxImg = 2 ; 
			entity->NumImage = 0 ;
			entity->TempImage = 3 ; 
		}
		if(entity->direction == LEFT)
		{
			if(entity->NumImage >= entity->NbmaxImg - 1 && entity->TempImage < 1)
			{
				entity->direction=RIGHT;
				entity->etat = IDLE ;
				entity->NbPas=0;
			}
		}
		else
		{
			if(entity->NumImage >= entity->NbmaxImg - 1 && entity->TempImage < 1)
			{
				entity->direction=LEFT;
				entity->etat = IDLE ;
				entity->NbPas=0;
			}
		}
	}
			
}
int collisionBB(Enemie Monster , Personne Hero , int disX , int y)
{
if( Monster.x >= Hero.PosEcran.x && Monster.y > Hero.PosEcran.y && ( Monster.x - ( Hero.PosEcran.x + PERSONNE_MAXW )) <= disX &&  (Monster.y - Hero.PosEcran.y) <= y ) 
{
	return 1 ;
}
if( Monster.x > Hero.PosEcran.x && Monster.y <= Hero.PosEcran.y && ( Monster.x -( Hero.PosEcran.x + PERSONNE_MAXW )) <= disX && ( Hero.PosEcran .y  - ( Monster.y + Monster.h )) <= y)
{
	return 3;
}
if(Monster.x < Hero.PosEcran.x && Monster.y >= Hero.PosEcran.y && (Hero.PosEcran.x   - (Monster.x + Monster.w ) )<= disX && ( Monster.y  -( Hero.PosEcran.y + PERSONNE_MAXH)) <= y ) 
{
	return 2;
}
if(Monster.x <= Hero.PosEcran.x && Monster.y < Hero.PosEcran.y && (Hero.PosEcran.x  - (Monster.x + Monster.w)) <= disX && ( Hero.PosEcran.y  - ( Monster.y + Monster.h )) <= y )
{
	return 4 ;
}
return 0 ;
}
void moveIA(Enemie *entity , Personne *Hero)
{
if( entity->life > 0)
{
switch(collisionBB(*entity ,*Hero,400, 200))
{
	case 1 : 
	if( entity-> i >= 3  && (SDL_GetTicks() - entity->Temp_entre2attack) >= 1000)
	{
		entity-> i = 0 ;
		if( collisionBB(*entity, *Hero , 20 , 20 ) == 1 )
			entity->etat = ATTACK ;
		else
			entity->etat = SUIVRE ;
	}
	if( entity->direction == RIGHT )
	{	
		entity->etat = TURN ;
		if(entity->NbmaxImg != 2)
		{
			entity->NbmaxImg = 2 ;
			entity->NumImage = 0 ; 
			entity->TempImage = 3; 
		}
		if(entity->NumImage >= entity->NbmaxImg - 1 && entity->TempImage < 1)
		{
			entity->direction = LEFT ;
			entity->NbPas = 0 ;
			entity->etat = SUIVRE ;
		}
	}
	if(entity->direction == LEFT && entity->etat == SUIVRE )
	{
		if( entity->NbmaxImg != 4 )
		{
			entity->NbmaxImg = 4 ;
			entity->NumImage = 0 ; 
			entity->TempImage = 3; 
			entity->SFX = 2 ;
		}
		
		if(entity->NumImage >= entity->NbmaxImg - 1 && entity->TempImage < 1)
		{
			entity->etat = RUN ;
			entity->SFX = 0 ;
		}
	}
	if(entity->etat == RUN && entity->direction == LEFT && entity->TempImage < 1) 
	{
	
		if( entity->NbmaxImg != 8 )
		{
			entity->NbmaxImg = 8 ;
			entity->NumImage = 0 ; 
			entity->TempImage = 3; 
			entity->SFX = 3 ;
		}
		if( entity->x  >  Hero->PosEcran.x  && (entity->NumImage == 3 || entity->NumImage == 7))
			entity->x -= SPEEDMAX_MONSTER ;
	}
	if( collisionBB(*entity, *Hero , 15 , 30) == 1 && entity->etat != TURN && entity->i < 3)
	{

		entity->etat = ATTACK ;
		if( entity->NbmaxImg != 12 )
		{
			entity->NbmaxImg = 12 ;
			entity->NumImage = 0 ; 
			entity->TempImage = 3; 
		}
		if( entity->NumImage == 7 )
		{
			entity->SFX  = 1 ;
			entity->x -= 5 ;
		}
		else
			entity->SFX  = 0 ;
		if(entity->NumImage >= entity->NbmaxImg -1 && entity->TempImage <1 )
		{
			entity->i ++ ;
			if( entity->i >= 3 )
			{
				entity-> Temp_entre2attack = SDL_GetTicks();
				entity->etat = STOP ; 
			}
		}
	}
	else if( collisionBB(*entity, *Hero , 100 , 30) != 1 && entity->etat != TURN && entity->i < 3)
		entity->etat = RUN  ;
	if( entity->etat == STOP && entity->direction == LEFT && entity->i >= 3 )
	{
	
		if( entity->NbmaxImg != 5 )
		{
			entity->NbmaxImg = 5 ;
			entity->NumImage = 0 ; 
			entity->TempImage = 3; 
		}
		if( (entity->NumImage == 1 || entity->NumImage ==2 ) && entity->TempImage <1 )
			entity->x += 40 ;
	}
	if( Hero->Attack == 1 && collisionBB(*entity , *Hero , 5 ,  5 ) == 1 && entity->etat != ATTACK )
	{
        	entity->SFX = 0 ;
        	entity->life--;
        	entity->x += 30 ;
        	if( entity->life <= 0 )
        		entity->etat = DEATH_AIR ;
	}
	else if( Hero->Attack != 1 && collisionBB(*entity , *Hero , 3 , 3 ) == 1 && entity->etat == ATTACK )
	{
		Hero->PosEcran.x -= 30 ;
        	Hero->vie--;
	}
	else if( Hero->Attack == 1 && entity->etat == ATTACK && collisionBB(*entity , *Hero , 0 , 0 ) == 1 )
	{
		entity->x += 30 ;
		Hero->PosEcran.x -= 30 ;
	}
break ; 
case 3 :
	if( entity-> i >= 3  && (SDL_GetTicks() - entity->Temp_entre2attack) >= 1000)
	{
		entity-> i = 0 ;
		if( collisionBB(*entity, *Hero , 20 , 20) == 3 )
			entity->etat = ATTACK ;
		else
			entity->etat = SUIVRE ;
	}
	if( entity->direction == RIGHT )
	{	
		entity->etat = TURN ;
		if(entity->NbmaxImg != 2)
		{
			entity->NbmaxImg = 2 ;
			entity->NumImage = 0 ; 
			entity->TempImage = 3; 
		}
		if(entity->NumImage >= entity->NbmaxImg - 1 && entity->TempImage < 1)
		{
			entity->direction = LEFT ;
			entity->NbPas = 0 ;
			entity->etat = SUIVRE ;
		}
	}
	if(entity->direction == LEFT && entity->etat == SUIVRE )
	{
		if( entity->NbmaxImg != 4 )
		{
			entity->NbmaxImg = 4 ;
			entity->NumImage = 0 ; 
			entity->TempImage = 3; 
			entity->SFX = 2 ;
		}
		
		if(entity->NumImage >= entity->NbmaxImg - 1 && entity->TempImage < 1)
		{
			entity->etat = RUN ;
			entity->SFX = 0 ;
		}
	}
	if(entity->etat == RUN && entity->direction == LEFT && entity->TempImage < 1) 
	{
		if( entity->NbmaxImg != 8 )
		{
			entity->NbmaxImg = 8 ;
			entity->NumImage = 0 ; 
			entity->TempImage = 3; 
			entity->SFX = 3 ;
		}
		if( entity->x >  Hero->PosEcran.x )
			entity->x -= SPEEDMAX_MONSTER ;
	}
	if( collisionBB(*entity, *Hero , 100 , 30) == 3 && entity->etat != TURN && entity->i < 3)
	{ 
		entity->etat = ATTACK ;
		if( entity->NbmaxImg != 12 )
		{
			entity->NbmaxImg = 12 ;
			entity->NumImage = 0 ; 
			entity->TempImage = 3; 
		}
		if( entity->NumImage == 7 )
		{
			entity->SFX  = 1 ;
			entity->x -= 5 ;
		}
		else
			entity->SFX  = 0 ;
		if( entity->NumImage >= entity->NbmaxImg -1 && entity->TempImage < 1 )
		{
			entity->i ++ ;
			if( entity->i >= 3 )
			{
				entity->Temp_entre2attack = SDL_GetTicks();
				entity->etat = STOP ; 
			}
		}
	}
	else if( collisionBB(*entity, *Hero , 100 , 30) != 3 && entity->etat != TURN && entity->i < 3)
		entity->etat = RUN  ;
	if( entity->etat == STOP && entity->direction == LEFT && entity->i >= 3 )
	{
		if( entity->NbmaxImg != 5 )
		{
			entity->NbmaxImg = 5 ;
			entity->NumImage = 0 ; 
			entity->TempImage = 3; 
		}
		if( (entity->NumImage == 1 || entity->NumImage ==2 ) && entity->TempImage <1 )
			entity->x += 40 ;
	}
	if( Hero->Attack == 1 && collisionBB(*entity , *Hero , 5 , 5) == 3 && entity->etat != ATTACK )
	{
        	entity->SFX = 0 ;
        	entity->life--;
        	entity->x += 30 ;
        	if( entity->life <= 0 )
        		entity->etat = DEATH_AIR ;
	}
	else if( Hero->Attack != 1 && collisionBB(*entity , *Hero , 3 ,  3 ) == 3 && entity->etat == ATTACK )
	{
		Hero->PosEcran.x -= 30 ;
        	Hero->vie--;
	}
	else if( Hero->Attack == 1 && entity->etat == ATTACK && collisionBB(*entity , *Hero , 0 , 0 ) == 3 )
	{
		entity->x += 30 ;
		Hero->PosEcran.x -= 30 ;
	}
	break;
case 4 :
	
	if( entity-> i >= 3  && (SDL_GetTicks() - entity->Temp_entre2attack) >= 1000)
	{
		entity-> i = 0 ;
		if( collisionBB(*entity, *Hero , 20 , 20) == 4 )
			entity->etat = ATTACK ;
		else
			entity->etat = SUIVRE ;
	}
	if( entity->direction == LEFT )
	{	
		entity->etat = TURN ;
		if(entity->NbmaxImg != 2)
		{
			entity->NbmaxImg = 2 ;
			entity->NumImage = 0 ; 
			entity->TempImage = 3; 
		}
		if(entity->NumImage >= entity->NbmaxImg - 1 && entity->TempImage < 1)
		{
			entity->direction = RIGHT ;
			entity->NbPas = 0 ;
			entity->etat = SUIVRE ;
		}
	}
	if(entity->direction == RIGHT && entity->etat == SUIVRE )
	{
		if( entity->NbmaxImg != 4 )
		{
			entity->NbmaxImg = 4 ;
			entity->NumImage = 0 ; 
			entity->TempImage = 3; 
			entity->SFX = 2 ;
		}
		
		if(entity->NumImage >= entity->NbmaxImg - 1 && entity->TempImage < 1)
		{
			entity->etat = RUN ;
			entity->SFX = 0 ;
		}
	}
	if(entity->etat == RUN && entity->direction == RIGHT && entity->TempImage < 1) 
	{
	
		if( entity->NbmaxImg != 8 )
		{
			entity->NbmaxImg = 8 ;
			entity->NumImage = 0 ; 
			entity->TempImage = 3; 
			entity->SFX = 3 ;
		}
		if( entity->x - SPEEDMAX_MONSTER <  Hero->PosEcran.x )
			entity->x += SPEEDMAX_MONSTER ;
	}
	if( collisionBB(*entity, *Hero , 15 , 30) == 4 && entity->etat != TURN && entity->i < 3)
	{
		entity->etat = ATTACK ;
		if( entity->NbmaxImg != 12 )
		{
			entity->NbmaxImg = 12 ;
			entity->NumImage = 0 ; 
			entity->TempImage = 3; 
		}
		if( entity->NumImage == 7 )
		{
			entity->SFX  = 1 ;
			entity->x += 5 ;
		}
		else
			entity->SFX  = 0 ;
		if(entity->NumImage >= entity->NbmaxImg -1 && entity->TempImage <1 )
		{
			entity->i ++ ;
			if( entity->i >= 3 )
			{
				entity-> Temp_entre2attack = SDL_GetTicks();
				entity->etat = STOP ; 
			}
		}
	}
	else if( collisionBB(*entity, *Hero , 100 , 30) != 4 && entity->etat != TURN && entity->i < 3)
		entity->etat = RUN  ;
	if( entity->etat == STOP && entity->direction == RIGHT && entity->i >= 3 )
	{
		if( entity->NbmaxImg != 5 )
		{
			entity->NbmaxImg = 5 ;
			entity->NumImage = 0 ; 
			entity->TempImage = 3; 
		}
		if( (entity->NumImage == 1 || entity->NumImage ==2 ) && entity->TempImage <1 )
			entity->x -= 40 ;
	}
	if( Hero->Attack == 1 && collisionBB(*entity , *Hero , 5 , 5 ) == 4 && entity->etat != ATTACK )
	{
        	entity->SFX = 0 ;
        	entity->life--;
        	entity->x -= 30 ;
        	if( entity->life <= 0 )
        		entity->etat = DEATH_AIR ;
	}
	else if( Hero->Attack != 1 && collisionBB(*entity , *Hero , 3 ,  3 ) == 4 && entity->etat == ATTACK )
	{
		Hero->PosEcran.x += 30 ;
        	Hero->vie--;
	}
	else if( Hero->Attack == 1 && entity->etat == ATTACK && collisionBB(*entity , *Hero , 0 , 0 ) == 3 )
	{
		entity->x -= 30 ;
		Hero->PosEcran.x += 30 ;
	}
	break;
case 2 :
	if( entity-> i >= 3  && (SDL_GetTicks() - entity->Temp_entre2attack) >= 1000)
	{
		entity-> i = 0 ;
		if( collisionBB(*entity, *Hero , 20 , 20) == 2 )
			entity->etat = ATTACK ;
		else
			entity->etat = SUIVRE ;
	}
	if( entity->direction == LEFT )
	{	
		entity->etat = TURN ;
		if(entity->NbmaxImg != 2)
		{
			entity->NbmaxImg = 2 ;
			entity->NumImage = 0 ; 
			entity->TempImage = 3; 
		}
		if(entity->NumImage >= entity->NbmaxImg - 1 && entity->TempImage < 1)
		{
			entity->direction = RIGHT ;
			entity->NbPas = 0 ;
			entity->etat = SUIVRE ;
		}
	}
	if(entity->direction == RIGHT && entity->etat == SUIVRE )
	{
		if( entity->NbmaxImg != 4 )
		{
			entity->NbmaxImg = 4 ;
			entity->NumImage = 0 ; 
			entity->TempImage = 3; 
			entity->SFX = 2 ;
		}
		
		if(entity->NumImage >= entity->NbmaxImg - 1 && entity->TempImage < 1)
		{
			entity->etat = RUN ;
			entity->SFX = 0 ;
		}
	}
	if(entity->etat == RUN && entity->direction == RIGHT && entity->TempImage < 1) 
	{
	
		if( entity->NbmaxImg != 8 )
		{
			entity->NbmaxImg = 8 ;
			entity->NumImage = 0 ; 
			entity->TempImage = 3; 
			entity->SFX = 3 ;
		}
		if( entity->x - SPEEDMAX_MONSTER <  Hero->PosEcran.x )
			entity->x += SPEEDMAX_MONSTER ;
	}
	if( collisionBB(*entity, *Hero , 15 , 30) == 2 && entity->etat != TURN && entity->i < 3)
	{
		entity->etat = ATTACK ;
		if( entity->NbmaxImg != 12 )
		{
			entity->NbmaxImg = 12 ;
			entity->NumImage = 0 ; 
			entity->TempImage = 3; 
		}
		if( entity->NumImage == 7 )
		{
			entity->SFX  = 1 ;
			entity->x += 5 ;
		}
		else
			entity->SFX  = 0 ;
		if(entity->NumImage >= entity->NbmaxImg -1 && entity->TempImage <1 )
		{
			entity->i ++ ;
			if( entity->i >= 3 )
			{
				entity-> Temp_entre2attack = SDL_GetTicks();
				entity->etat = STOP ; 
			}
		}
	}
	else if( collisionBB(*entity, *Hero , 100 , 30) != 2 && entity->etat != TURN && entity->i < 3)
		entity->etat = RUN  ;
	if( entity->etat == STOP && entity->direction == RIGHT && entity->i >= 3 )
	{
		if( entity->NbmaxImg != 5 )
		{
			entity->NbmaxImg = 5 ;
			entity->NumImage = 0 ; 
			entity->TempImage = 3; 
		}
		if( (entity->NumImage == 1 || entity->NumImage ==2 ) && entity->TempImage <1 )
			entity->x -= 40 ;
	}
	if( Hero->Attack == 1 && collisionBB(*entity , *Hero , 5 , 5) == 2 && entity->etat != ATTACK )
	{
        	entity->SFX = 0 ;
        	entity->life-- ;
        	entity->x -= 30 ;
        	if( entity->life <= 0 )
        		entity->etat = DEATH_AIR ;
	}
	else if( Hero->Attack != 1 && collisionBB(*entity , *Hero , 3 , 3 ) == 2 && entity->etat == ATTACK )
	{
		Hero->PosEcran.x += 30 ;
        	Hero->vie--;
	}
	else if( Hero->Attack == 1 && entity->etat == ATTACK && collisionBB(*entity , *Hero , 0 , 0 ) == 2 )
	{
		entity->x -= 30 ;
		Hero->PosEcran.x += 30 ;
	}
	break;
case 0 :
	entity->etat = IDLE ; 
break ;
}
printf("\ncol:%d \t i1:%d ",collisionBB(*entity ,*Hero,400, 200) , entity->i);
}
else 
{
	if( entity->etat != DEATH_LAND )
	{
		if( entity->NbmaxImg != 2 )
		{
			entity->NumImage = 0 ;
			entity->TempImage = 3 ;
			entity->NbmaxImg = 2 ;
		}
	if( entity->NumImage >= entity->NbmaxImg - 1 && entity->TempImage < 1 )	
		entity->etat = DEATH_LAND ;
	}
	if( entity->etat == DEATH_LAND )
	{
		if( entity->NbmaxImg != 3 )
		{
			entity->NumImage = 0 ;
			entity->TempImage = 3 ;
			entity->NbmaxImg = 3 ;
		}
		if( entity->NumImage >= entity->NbmaxImg - 1 && entity->TempImage < 1 )	
			entity->etat = DEATH ;
	}
}
playSoundFx_monster(*entity);
if(entity->x > Hero->PosEcran.x)
	Mix_Volume(-1 ,25*MIX_MAX_VOLUME/(entity->x - Hero->PosEcran.x + 1)); 
else
	Mix_Volume(-1 ,25*MIX_MAX_VOLUME/(Hero->PosEcran.x - entity->x + 1)); 
}
void playSoundFx_monster(Enemie entity) 
{
switch (entity.etat)
    {
        case IDLE:
        	Mix_PlayChannelTimed(-1,entity.Walk, 0 ,700);
        break;
        case SUIVRE:
        	Mix_AllocateChannels(1);
        	if(entity.SFX == 2)    
            		Mix_PlayChannel(-1,entity.Prepare, 0);
        break;
        case ATTACK : 
        	Mix_AllocateChannels(1);
        	if( entity.SFX == 1 )      
                	Mix_PlayChannel(-1, entity.Sword, 0);
        break;
        case RUN:  
        	Mix_AllocateChannels(2);
        	if( entity.SFX == 3 )   
                	Mix_PlayChannelTimed(-1, entity.Run, 0 , 600);  
        break;
   }
}
void AfficheImage(Image I , SDL_Surface *IMAGE)
{
	SDL_BlitSurface(I.Img,NULL,IMAGE,&(I.Pos));
}
void cleanupMusic(Mix_Chunk *MUSIC)
{
if(MUSIC!=NULL)
	Mix_FreeChunk(MUSIC);
}
