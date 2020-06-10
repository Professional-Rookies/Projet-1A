#include "enigme_fcp.h"

void enigme_cpf(SDL_Surface *screen, hero *h)
{

    static int continuer = 1;
    static SDL_Event event;
    static int rang = 0;
    static int cpc;
    static int res;
    static enigme_fcp e;
    static int once = 0;
    static text resol;

    if (!once)
    {
        initialiser_enigme_fcp(&e);
        initialiser_text(&resol, "", 300, 300, 30);
        once = 1;
    }

    screen = SDL_SetVideoMode(e.plan->w, e.plan->h, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

    while (continuer)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_DOWN:
                    if (rang == 0)
                    {
                        e.ciseaux = IMG_Load("../img/enigme/PCA.png");
                        e.pierre = IMG_Load("../img/enigme/PP.png");
                        e.feuille = IMG_Load("../img/enigme/PF.png");
                        rang = 1;
                    }
                    else if (rang == 1)
                    {
                        e.ciseaux = IMG_Load("../img/enigme/PC.png");
                        e.pierre = IMG_Load("../img/enigme/PPA.png");
                        e.feuille = IMG_Load("../img/enigme/PF.png");
                        rang = 2;
                    }
                    else if (rang == 2)
                    {
                        e.ciseaux = IMG_Load("../img/enigme/PC.png");
                        e.pierre = IMG_Load("../img/enigme/PP.png");
                        e.feuille = IMG_Load("../img/enigme/PFA.png");
                        rang = 3;
                    }
                    break;
                case SDLK_UP:
                    if (rang == 0)
                    {
                        e.ciseaux = IMG_Load("../img/enigme/PC.png");
                        e.pierre = IMG_Load("../img/enigme/PP.png");
                        e.feuille = IMG_Load("../img/enigme/PFA.png");
                        rang = 3;
                    }
                    else if (rang == 3)
                    {
                        e.ciseaux = IMG_Load("../img/enigme/PC.png");
                        e.pierre = IMG_Load("../img/enigme/PPA.png");
                        e.feuille = IMG_Load("../img/enigme/PF.png");
                        rang = 2;
                    }
                    else if (rang == 2)
                    {
                        e.ciseaux = IMG_Load("../img/enigme/PCA.png");
                        e.pierre = IMG_Load("../img/enigme/PP.png");
                        e.feuille = IMG_Load("../img/enigme/PF.png");
                        rang = 1;
                    }
                    break;
                case SDLK_RETURN:
                    if (rang == 1)
                        e.choix_hero = 1;
                    else if (rang == 2)
                        e.choix_hero = 2;
                    else if (rang == 3)
                        e.choix_hero = 3;
                    SDL_Delay(1000);
                    e.choix_ordinateur = choix_pc(e);
                    break;
                }
                break;
            }
            res = resolution_enigme_fcp(e);
            if (res == 0)
            {
                resol.text = TTF_RenderText_Blended(resol.font, "TIE", resol.color);
                continuer = 0;
                SDL_Delay(1000);
            }

            else if (res == 1)
            {
                resol.text = TTF_RenderText_Blended(resol.font, "YOU WIN", resol.color);
                h->score_hero.valeur_score += 10;
                continuer = 0;
                SDL_Delay(1000);
            }
            else if (res == 2)
            {
                resol.text = TTF_RenderText_Blended(resol.font, "YOU LOSE", resol.color);
                h->score_hero.valeur_score -= 10;
                continuer = 0;
                SDL_Delay(1000);
            }
            printf("RES: %d\n", res);
            printf("CPC: %d\n", e.choix_ordinateur);
            printf("CH: %d\n", e.choix_hero);
            SDL_BlitSurface(e.plan, NULL, screen, &e.position_plan);
            SDL_BlitSurface(e.ciseaux, NULL, screen, &e.position_ciseaux);
            SDL_BlitSurface(e.pierre, NULL, screen, &e.position_pierre);
            SDL_BlitSurface(e.feuille, NULL, screen, &e.position_feuille);
            SDL_BlitSurface(resol.text, NULL, screen, &resol.position);
            SDL_Flip(screen);
        }
    }
}
int choix_pc(enigme_fcp e)
{
    srand(time(NULL));
    e.choix_ordinateur = rand() % (3 - 1) + 1;
    return e.choix_ordinateur;
}
int resolution_enigme_fcp(enigme_fcp e)
{
    if (e.choix_hero == e.choix_ordinateur)
        e.resolution = 0;

    if (e.choix_hero == 1)
    {
        if (e.choix_ordinateur == 3)
            return 1;
        else
        {
            return 2;
        }
    }
    if (e.choix_hero == 2)
    {
        if (e.choix_ordinateur == 1)
            return 1;
        else
        {
            return 2;
        }
    }
    if (e.choix_hero == 3)
    {
        if (e.choix_ordinateur == 2)
        {
            return 1;
        }
        else
        {
            return 2;
        }
    }

    /*else if (e.choix_hero - e.choix_ordinateur == -1 || e.choix_hero - e.choix_ordinateur == 2)
        e.resolution = 2;
    else if (e.choix_hero - e.choix_ordinateur == -2 || e.choix_hero - e.choix_ordinateur == 1)
        e.resolution = 1;*/
}

void initialiser_enigme_fcp(enigme_fcp *e)
{
    e->plan = IMG_Load("../img/enigme/plan.jpg");
    e->ciseaux = IMG_Load("../img/enigme/PC.png");
    e->pierre = IMG_Load("../img/enigme/PP.png");
    e->feuille = IMG_Load("../img/enigme/PF.png");
    e->position_plan.x = 0;
    e->position_plan.y = 0;

    e->position_ciseaux.x = 200;
    e->position_ciseaux.y = 100;

    e->position_pierre.x = 200;
    e->position_pierre.y = 200;

    e->position_feuille.x = 200;
    e->position_feuille.y = 300;

    e->choix_hero = -1;
    e->choix_ordinateur = -1;
    e->resolution = -1;
}
