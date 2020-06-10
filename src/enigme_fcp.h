#ifndef FCP_H
#define FCP_H
#include <stdio.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <time.h>

#include "hero.h"
#include "background.h"
typedef struct Enigme_fcp
{
    SDL_Surface *plan;
    SDL_Surface *pierre;
    SDL_Surface *ciseaux;
    SDL_Surface *feuille;
    SDL_Rect position_plan;
    SDL_Rect position_pierre;
    SDL_Rect position_ciseaux;
    SDL_Rect position_feuille;
    int choix_hero;
    int choix_ordinateur;
    int resolution;

} enigme_fcp;

void enigme_cpf(SDL_Surface *screen, hero *h);
int choix_pc(enigme_fcp e);
int resolution_enigme_fcp(enigme_fcp e);
void initialiser_enigme_fcp(enigme_fcp *e);
#endif
