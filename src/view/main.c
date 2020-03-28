/*
    GNU/Linux et MacOS
        > gcc main.c $(sdl2-config --cflags --libs) -o prog
        > gcc *.c $(sdl2-config --cflags --libs) -o prog
    Windows
        > gcc src/main.c -o bin/prog -I include -L lib -lmingw32 -lSDL2main -lSDL2
        > gcc src/main.c -o bin/prog -I include -L lib -lmingw32 -lSDL2main -lSDL2 -mwindow_s
*/
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define WIDTH 800
#define HEIGHT 450

int fenetreMenu(void);
int fenetreJeu(void);

void SDL_ExitWithError(const char *message);

int main(int argc, char *argv[])
{

    //Lancement SDL
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
        SDL_ExitWithError("Initialisation SDL");
    if(TTF_Init() == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    if (fenetreMenu() != 0)
    {
        SDL_ExitWithError("Erreur fenetre");
    }
    TTF_Quit();
    SDL_Quit();
    
    return EXIT_SUCCESS;
}
int fenetreMenu(){
    SDL_Window *window_menu = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_bool fenetre_lance = SDL_TRUE;


        //Création fenêtre + rendu
    if (SDL_CreateWindowAndRenderer(WIDTH,HEIGHT,0,&window_menu,&renderer) != 0)
    {
        SDL_ExitWithError("Erreur création fenêtre & renderer");
    }

    if(window_menu == NULL)
        SDL_ExitWithError("Creation fenetre echouee");

    /*------------------------------------------------------------*/

    /********* AFFICHAGE IMAGE TECHNIQUE 1 *********//*
    SDL_Surface *image_fond = NULL;
    SDL_Texture *texture = NULL;

    image_fond = SDL_LoadBMP("ressources/fond_fenetre2.bmp");

    if (image_fond == NULL){
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window_menu);
        SDL_ExitWithError("Erreur chargement image");
    }

    texture = SDL_CreateTextureFromSurface(renderer, image_fond);
    SDL_FreeSurface(image_fond);

    if(texture == NULL){
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window_menu);
        SDL_ExitWithError("Erreur chargement texture");
    }

    SDL_Rect rectangle_img;

    if(SDL_QueryTexture(texture, NULL, NULL, &rectangle_img.w, &rectangle_img.h) != 0){
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window_menu);
        SDL_ExitWithError("Erreur chargement texture");
    }

    rectangle_img.x = (WIDTH - rectangle_img.w)/2;
    rectangle_img.y = (HEIGHT - rectangle_img.h)/2;

    if(SDL_RenderCopy(renderer,texture,NULL, &rectangle_img) != 0){
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window_menu);
        SDL_ExitWithError("Erreur affichage texture"); 
    }

    SDL_RenderPresent(renderer);

    /********* AFFICHAGE IMAGE TECHNIQUE 2 *********/
    TTF_Font *font1 = NULL;
    font1 = TTF_OpenFont( "../../ressources/fonts/BebasNeue-Regular.ttf", 50);
    if (font1 == NULL)
    {
        printf("voilà\n");
    }
    SDL_Color textColorN = { 0, 0, 0, 255 };
    SDL_Surface *message = NULL;


    SDL_Surface *Surf_fenetre_menu=NULL;
    SDL_Surface *imagedefond_menu=NULL;



    imagedefond_menu = SDL_LoadBMP("../../ressources/img/fond_fenetre2.bmp");
    if (imagedefond_menu == NULL)
    {
        printf("C NUL\n");
    }
    Surf_fenetre_menu = SDL_GetWindowSurface(window_menu);
    SDL_BlitSurface(imagedefond_menu,NULL,Surf_fenetre_menu,NULL);

    SDL_Rect position_txt_title ={(WIDTH-553)/2,20,0,0};
    imagedefond_menu = SDL_LoadBMP("../../ressources/img/title.bmp");
    SDL_BlitSurface(imagedefond_menu, NULL, Surf_fenetre_menu,&position_txt_title);

    SDL_Rect position_txt_option ={(WIDTH-50)/2,100,0,0};
    message = TTF_RenderText_Solid( font1, "Option", textColorN);
    SDL_BlitSurface(message, NULL, Surf_fenetre_menu,&position_txt_option);

    SDL_UpdateWindowSurface(window_menu);
    
    while(fenetre_lance){
        SDL_Event evenement_fenetre;
        while(SDL_PollEvent(&evenement_fenetre)){
            switch(evenement_fenetre.type){
                case SDL_MOUSEBUTTONDOWN:
                    printf("%d / %d\n",evenement_fenetre.button.x,evenement_fenetre.button.y );
                    if (evenement_fenetre.button.y > HEIGHT/2)
                    {
                        printf("Je suis bien à la moitié\n");
                        //On peut ouvrir la fenêtre de loïck
                    }
                    break;


                case SDL_QUIT:
                    fenetre_lance = SDL_FALSE;
                    break;
                default:
                    break;
            }
        }
    }
    /*------------------------------------------------------------*/
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window_menu);
    return 0;

}

void SDL_ExitWithError(const char *message)
{
    SDL_Log("ERREUR : %s > %s\n", message, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}

