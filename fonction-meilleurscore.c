#include "header.h"

#include<stdio.h>
#include<stdlib.h>
#include <SDL/SDL.h>
#include<SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
void init_image(image *i)
{

    i->img = IMG_Load("Final.png");
    if (i->img == NULL)
        printf("image nexite pas\n");
    i->pos.x = 0;
    i->pos.y = 0;
    
    
    
}



void InitBouton(image *B,char Buttom[],int X,int Y)
{
B->img=IMG_Load(Buttom);
if(B->img==NULL)
{
	return;	
}
B->pos.x=X;
B->pos.y=Y;
B->pos.w=B->img->w;
B->pos.h=B->img->h;
}
void afficher(image i, SDL_Surface *ecran)
{
    SDL_BlitSurface(i.img, NULL, ecran, &i.pos);
}


void showTopThreeScores(SDL_Surface *screen)
{
   
    TTF_Font* font = TTF_OpenFont("textt.ttf", 70);
    Score Score,Tabs[100000],aux;

    int i=0,n=0;
    // Open the score file for reading
    FILE *fp = fopen("score.txt", "r");
    if (fp == NULL) {
        printf("Error: unable to open score file\n");
        return;
    }
    else
    {
    	
       while(fscanf(fp,"%s %d",Tabs[n].Nom,&Tabs[n].scoreActuel)!=EOF)
        {
            n++;
           
           
        }
    for(i=0;i<n;i++)
    {
        printf("\n Tableau %d %s %d\n",i,Tabs[i].Nom,Tabs[i].scoreActuel);
    }
    // Close the score file
   
    int permut;
    //trie
            do
            {
                permut = 0;
                for( i = 0 ; i < n-1 ; i++ )
                {
                    if ( Tabs[i].scoreActuel < Tabs[i+1].scoreActuel )
                    {
                        aux= Tabs[i];
                        Tabs[i] = Tabs[i+1];
                        Tabs[i+1]= aux ;
                        permut = 1;
                    }
                }
            }
            while (permut == 1);
    // Draw the scores on the screen
    char string[20];
    SDL_Surface *textSurface;
      SDL_Surface *texteScore;
    SDL_Rect textPosition;
     
     
     for (i = 0; i < 3; i++) {
        SDL_Color textColor = {255, 255, 255};
        sprintf(string, "%s %d ",Tabs[i].Nom,Tabs[i].scoreActuel);
       texteScore =TTF_RenderText_Blended(font,string,textColor);
        textPosition.x=490;
        textPosition.y=90+ 61*i;
        SDL_BlitSurface(texteScore, NULL, screen, &textPosition);
        
        }
        
      fclose(fp);
      }
}
  //  SDL_Flip(screen);




void cleanup(SDL_Surface *IMAGE)
{
if(IMAGE!=NULL)
	SDL_FreeSurface(IMAGE);
}


























