#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
typedef struct perso{
	SDL_Surface *perso[5][9];
	SDL_Rect PosEcran;
	int Direction,vie,score,vitesse_saut,sprite,up;
	double vitesse, acceleration;
	Mix_Chunk *bref;
}Personne;
void init (Personne * p, int numperso);
void initPerso(Personne *p);
void afficherPerso(Personne p, SDL_Surface * screen);
void movePerso (Personne *p, uint32_t dt);
void animerPerso (Personne* p);
void saut(Personne *p,int dt, int posinit);
