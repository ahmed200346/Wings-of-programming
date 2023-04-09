#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
typedef struct perso{
	SDL_Surface *perso[5][9];
	SDL_Rect PosEcran,PosEcranRel;
	int Direction,vie,score,sprite,up;
	double vitesse,acceleration,vitesse_saut,dx;
	Mix_Chunk *bref;
}Personne;
typedef struct
{
	char *url;
	SDL_Rect pos_map,pos_perso;
	SDL_Surface *img,*perso;
}map;
void init (Personne * p, int numperso);
void initPerso(Personne *p);
void afficherPerso(Personne p, SDL_Surface * screen);
void movePerso (Personne *p, uint32_t dt);
void animerPerso (Personne* p);
void saut(Personne *p,int dt, int posx_absolu,int posy_absolu);
void scrolling(SDL_Rect *b,int direction,double pas);
void initmap(map *m);
void afficherminimap(map m,SDL_Surface *screen);
void affichertemps(uint32_t start_time,SDL_Surface *screen);
