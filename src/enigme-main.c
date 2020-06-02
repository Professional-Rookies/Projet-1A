#include "pendu.h"

int enigme_pendu(SDL_Surface *screen, hero *h)
{
	const char *INVISIBLE_CHAR = "-";
	SDL_Surface *background = NULL;
	SDL_Rect positionBackground;

	SDL_Surface *texteTitre = NULL;
	SDL_Rect positionTextTitre;
	SDL_Color couleurTitre = {125, 65, 10};
	TTF_Font *policeTitre = NULL;

	SDL_Surface *texteMot = NULL;
	SDL_Rect positionTextMot;
	SDL_Color couleurMot = {255, 255, 255};
	TTF_Font *policeMot = NULL;
	SDL_Surface *texte;
	SDL_Rect positionText;

	SDL_Surface *FINAL = NULL;
	SDL_Rect positionFINAL;

	positionFINAL.x = 300;
	positionFINAL.y = 200;

	SDL_Event event;
	int continuer = 1;

	if (TTF_Init() == -1)
	{
		fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
		exit(EXIT_FAILURE);
	}

	/*if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		printf("unable to initialize SDL : %s\n", SDL_GetError());
		return 1;
	}*/
	screen = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	if (screen == NULL)
	{
		printf("unable to set video mode : %s\n", SDL_GetError());
		return 1;
	}
	SDL_WM_SetCaption("--- Enigme Find The Hidden Word --- ", NULL);
	SDL_ShowCursor(0);
	background = IMG_Load("../img/enigme/background.jpg");
	if (background == NULL)
	{
		printf("unable to set load bitmap : %s\n", SDL_GetError());
		return 1;
	}
	SDL_Surface *image;
	image = IMG_Load("../img/enigme/pendu-1.png");
	SDL_Rect positionImage;
	positionImage.x = 0;
	positionImage.y = 0;

	srand(time(NULL));
	int positionMot = rand() / (double)RAND_MAX * (NB_WORD - 1);
	char *word = NULL;

	FILE *fp = fopen("../txt_files/Quiz.txt", "r");
	int count = 0;
	char buf[MAX_LEN];
	while (fgets(buf, sizeof buf, fp) != NULL)
	{
		if (count == positionMot)
		{
			char *p = strchr(buf, '\n');

			if (p != NULL)
			{
				*p = 0;
			}
			word = malloc(strlen(buf) + 1);

			if (word != NULL)
			{
				strcpy(word, buf);
			}
			break;
		}
		count++;
	}
	fclose(fp);

	policeTitre = TTF_OpenFont("../fonts/infos.ttf", 45);
	texteTitre = TTF_RenderText_Blended(policeTitre, "Le Pendu", couleurTitre);
	positionTextTitre.x = 220;
	positionTextTitre.y = 15;

	positionBackground.x = 0;
	positionBackground.y = 0;

	policeMot = TTF_OpenFont("../fonts/table.ttf", 45);
	texteMot = TTF_RenderText_Blended(policeMot, word, couleurMot);
	positionTextMot.x = 250;
	positionTextMot.y = 250;

	char wordHidden[MAX_LEN];
	strcpy(wordHidden, word);

	int i;
	for (i = 0; i < strlen(word); i++)
		wordHidden[i] = '-';
	policeMot = TTF_OpenFont("../fonts/table.ttf", 45);
	texte = TTF_RenderText_Blended(policeMot, wordHidden, couleurMot);
	positionText.x = 300;
	positionText.y = 300;

	int nombrelettre = 0;
	int j;
	int t = 12, rang = 0;
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
			default:
				if (event.key.keysym.sym >= SDLK_a && event.key.keysym.sym <= SDLK_z)
				{
					t--;
					char c = toupper(event.key.keysym.sym);
					if (strchr(word, c) != 0)
					{

						for (j = 0; j < strlen(word); j++)
						{
							if (word[j] == c && wordHidden[j] == '-')
							{
								wordHidden[j] = c;
								nombrelettre++;
								t++;
							}
							texte = TTF_RenderText_Blended(policeMot, wordHidden, couleurMot);
						}
					}
					else
					{
						rang++;
						break;
					}
				}
				break;
			case SDL_KEYUP:
				break;
			}
			switch (rang)
			{
			case 1:
				image = IMG_Load("../img/enigme/pendu-2.png");
				break;
			case 2:
				image = IMG_Load("../img/enigme/pendu-3.png");
				break;
			case 3:
				image = IMG_Load("../img/enigme/pendu-4.png");
				break;
			case 4:
				image = IMG_Load("../img/enigme/pendu-5.png");
				break;
			case 5:
				image = IMG_Load("../img/enigme/pendu-6.png");
				break;
			case 6:
				image = IMG_Load("../img/enigme/pendu-7.png");
				break;
			case 7:
				image = IMG_Load("../img/enigme/pendu-8.png");
				break;
			case 8:
				image = IMG_Load("../img/enigme/pendu-9.png");
				break;
			case 9:
				image = IMG_Load("../img/enigme/pendu-10.png");
				break;
			case 10:
				image = IMG_Load("../img/enigme/pendu-11.png");
				break;
			case 11:
				image = IMG_Load("../img/enigme/pendu-12.png");
				break;
			}
			if (nombrelettre == strlen(word))
			{
				FINAL = IMG_Load("../img/enigme/gained.png");
				h->score_hero.valeur_score+=20;
				continuer = 0;
			}
			else if (t == 0 || rang > 12)
			{
				FINAL = IMG_Load("../img/enigme/lost.png");
				h->score_hero.valeur_score-=20;
				continuer = 0;
			}
		}
		SDL_BlitSurface(background, NULL, screen, &positionBackground);
		SDL_BlitSurface(image, NULL, screen, &positionImage);
		SDL_BlitSurface(texteTitre, NULL, screen, &positionTextTitre);
		SDL_BlitSurface(texteMot, NULL, screen, &positionTextMot);
		SDL_BlitSurface(texte, NULL, screen, &positionText);
		SDL_BlitSurface(FINAL, NULL, screen, &positionFINAL);
		SDL_Flip(screen);
		if (continuer == 0)
		{
			SDL_Delay(1500);
		}
	}

	SDL_FreeSurface(background);
	TTF_CloseFont(policeTitre);
	TTF_CloseFont(policeMot);
	TTF_Quit();
	SDL_FreeSurface(texteTitre);
	SDL_FreeSurface(texteMot);

}
