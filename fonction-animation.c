#include"header-animation.h"
void init_image(image * i){
i->nb_img=10;
FILE* fich;
fich=fopen("date.txt","r");
    i->img_actuelle=0;
    char nameIMG[35];
    
    
    
    //parcoure
    int ip;

   for ( ip = 0; ip < 35; ip++)
    {
    
        fscanf(fich,"%s",nameIMG);
        i->img[ip] = IMG_Load(nameIMG);
    }
i->pos.x=440;
i->pos.y=290;
i->pos.w=945;
i->pos.h=709;
}
void affiche(image * i,SDL_Surface *screen){
 SDL_BlitSurface(i->img[i->img_actuelle],NULL,screen,&i->pos);
    i->img_actuelle++;
    if (i->img_actuelle == 35) i->img_actuelle=0;}

void liberer(image * i)
{
    int ip;
    for ( ip = 0; ip < i->nb_img; ip++)
    {
       SDL_FreeSurface(i->img[ip]);
    }
}
