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
int affichageMenu(SDL_Surface *Surf_fenetre_menu , SDL_Surface *imagedefond_menu,SDL_Surface *imagedetitre_menu,SDL_bool option_select,SDL_bool quitter_select);
int affichageChoix(SDL_Surface *Surf_fenetre_menu , SDL_Surface *imagedefond_menu,int choixChanson);

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

int affichageChoix(SDL_Surface *Surf_fenetre_menu , SDL_Surface *imagedefond_menu,int choixChanson){
    TTF_Font *font1 = NULL;
    font1 = TTF_OpenFont( "../../ressources/fonts/BebasNeue-Regular.ttf", 50);
    if (font1 == NULL)
    {
        printf("voilà\n");
    }

    SDL_Color textColorNormal = { 0, 0, 0, 180 };
    SDL_Color textColorSelect = { 255, 48, 25, 255 };
    SDL_Surface *message = NULL;


    SDL_BlitSurface(imagedefond_menu,NULL,Surf_fenetre_menu,NULL);

    SDL_Rect position_txt_chanson1 ={(WIDTH-230)/2,150,0,0};

        
    if (choixChanson == 1)
    {
        message = TTF_RenderText_Solid( font1, "chanson1", textColorNormal);
    }else{
        message = TTF_RenderText_Solid( font1, "chanson1", textColorSelect);
    }
    SDL_BlitSurface(message, NULL, Surf_fenetre_menu,&position_txt_chanson1);

    SDL_Rect position_txt_chanson2 ={(WIDTH-100)/2,300,0,0};
    if (choixChanson == 2)
    {
        message = TTF_RenderText_Solid( font1, "chanson2", textColorNormal);
    }else{
        message = TTF_RenderText_Solid( font1, "chanson2", textColorSelect);
    }
    SDL_BlitSurface(message, NULL, Surf_fenetre_menu,&position_txt_chanson2);



    return 0;
}


int affichageMenu(SDL_Surface *Surf_fenetre_menu , SDL_Surface *imagedefond_menu,SDL_Surface *imagedetitre_menu,SDL_bool option_select,SDL_bool quitter_select){
    TTF_Font *font1 = NULL;
    font1 = TTF_OpenFont( "../../ressources/fonts/BebasNeue-Regular.ttf", 50);
    if (font1 == NULL)
    {
        printf("voilà\n");
    }

    SDL_Color textColorNormal = { 0, 0, 0, 180 };
    SDL_Color textColorSelect = { 150, 150, 20, 255 };
    SDL_Surface *message = NULL;


    SDL_BlitSurface(imagedefond_menu,NULL,Surf_fenetre_menu,NULL);
    SDL_Rect position_txt_title ={(WIDTH-553)/2,20,0,0};
    
    SDL_BlitSurface(imagedetitre_menu, NULL, Surf_fenetre_menu,&position_txt_title);

    SDL_Rect position_txt_option ={(WIDTH-230)/2,150,0,0};

        
    if (option_select == SDL_FALSE)
    {
        message = TTF_RenderText_Solid( font1, "Choix chanson", textColorNormal);
    }else{
        message = TTF_RenderText_Solid( font1, "Choix chanson", textColorSelect);
    }
    SDL_BlitSurface(message, NULL, Surf_fenetre_menu,&position_txt_option);

    SDL_Rect position_txt_quitter ={(WIDTH-100)/2,300,0,0};
    if (quitter_select == SDL_FALSE)
    {
    message = TTF_RenderText_Solid( font1, "Quitter", textColorNormal);
    }else{
        message = TTF_RenderText_Solid( font1, "Quitter", textColorSelect);
    }
    SDL_BlitSurface(message, NULL, Surf_fenetre_menu,&position_txt_quitter);



    return 0;
}

int fenetreChoix(){
    SDL_Window *window_choix = NULL;
    SDL_bool fenetre_lance = SDL_TRUE;
    int choixChanson = 0;


    window_choix = SDL_CreateWindow("HérosDeLaGuitare2i - choix",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WIDTH,HEIGHT,0);
    if(window_choix == NULL)
        SDL_ExitWithError("Creation fenetre echouee");

    SDL_Surface *Surf_fenetre_choix=NULL;
    SDL_Surface *imagedefond_choix=NULL;

    imagedefond_choix = SDL_LoadBMP("../../ressources/img/old-parchment.bmp");
    if (imagedefond_choix == NULL)
    {
        printf("C NUL\n");
    }
    Surf_fenetre_choix = SDL_GetWindowSurface(window_choix);
    
    affichageChoix(Surf_fenetre_choix,imagedefond_choix, choixChanson);

    SDL_UpdateWindowSurface(window_choix);

    

    
    
    while(fenetre_lance){
        

        SDL_Event evenement_fenetre;

        while(SDL_PollEvent(&evenement_fenetre)){
            switch(evenement_fenetre.type){
                case SDL_MOUSEBUTTONDOWN:
                    printf("%d / %d\n",evenement_fenetre.button.x,evenement_fenetre.button.y );
                    if (evenement_fenetre.button.x > 280 && evenement_fenetre.button.x < 520 &&
                        evenement_fenetre.button.y > 160 && evenement_fenetre.button.y < 200){
                        /*SDL_DestroyWindow(window_choix);
                        SDL_FreeSurface(imagedefond_choix);
                        SDL_FreeSurface(Surf_fenetre_choix);
                        SDL_FreeSurface(imagedetitre_choix);
                        fenetreChoix();*/
                    }
                    break;

                case SDL_MOUSEMOTION:
                        //printf("%d / %d\n",evenement_fenetre.motion.x,evenement_fenetre.motion.y );
                        if (evenement_fenetre.motion.x > 280 && evenement_fenetre.motion.x < 520 &&
                            evenement_fenetre.motion.y > 160 && evenement_fenetre.motion.y < 200){

                            if (choixChanson !=1)
                            {
                                choixChanson = 1;
                                affichageChoix(Surf_fenetre_choix,imagedefond_choix, choixChanson);
                                SDL_UpdateWindowSurface(window_choix);
                            }
                        }else{
                            if (choixChanson == 1)
                            {
                                choixChanson = 0;
                                affichageChoix(Surf_fenetre_choix,imagedefond_choix, choixChanson);
                                SDL_UpdateWindowSurface(window_choix);
                            }
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
    SDL_DestroyWindow(window_choix);
    return 0;

}

int fenetreMenu(){
    SDL_Window *window_menu = NULL;
    SDL_bool fenetre_lance = SDL_TRUE;

    //création fenêtre
    window_menu = SDL_CreateWindow("HérosDeLaGuitare2i",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WIDTH,HEIGHT,0);

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
    
    SDL_bool option_select = SDL_FALSE;
    SDL_bool quitter_select = SDL_FALSE;
    


    SDL_Surface *Surf_fenetre_menu=NULL;
    SDL_Surface *imagedefond_menu=NULL;
    SDL_Surface *imagedetitre_menu=NULL;

    imagedefond_menu = SDL_LoadBMP("../../ressources/img/fond_fenetre2.bmp");
    if (imagedefond_menu == NULL)
    {
        printf("C NUL\n");
    }
    Surf_fenetre_menu = SDL_GetWindowSurface(window_menu);

    imagedetitre_menu = SDL_LoadBMP("../../ressources/img/title.bmp");


    
    affichageMenu(Surf_fenetre_menu,imagedefond_menu,imagedetitre_menu, option_select, quitter_select);

    SDL_UpdateWindowSurface(window_menu);

    

    
    
    while(fenetre_lance){
        

        SDL_Event evenement_fenetre;

        while(SDL_PollEvent(&evenement_fenetre)){
            switch(evenement_fenetre.type){
                case SDL_MOUSEBUTTONDOWN:
                    printf("%d / %d\n",evenement_fenetre.button.x,evenement_fenetre.button.y );
                    if (evenement_fenetre.button.x > 280 && evenement_fenetre.button.x < 520 &&
                        evenement_fenetre.button.y > 160 && evenement_fenetre.button.y < 200){
                        SDL_DestroyWindow(window_menu);
                        SDL_FreeSurface(imagedefond_menu);
                        SDL_FreeSurface(Surf_fenetre_menu);
                        SDL_FreeSurface(imagedetitre_menu);
                        fenetre_lance = SDL_FALSE;
                        fenetreChoix();
                    }
                    if (evenement_fenetre.button.x > 350 && evenement_fenetre.button.x < 480 &&
                            evenement_fenetre.button.y > 310 && evenement_fenetre.button.y < 350){
                        fenetre_lance = SDL_FALSE;
                    }
                    break;

                case SDL_MOUSEMOTION:
                        //printf("%d / %d\n",evenement_fenetre.motion.x,evenement_fenetre.motion.y );
                        if (evenement_fenetre.motion.x > 280 && evenement_fenetre.motion.x < 520 &&
                            evenement_fenetre.motion.y > 160 && evenement_fenetre.motion.y < 200){

                            if (option_select == SDL_FALSE)
                            {
                                option_select = SDL_TRUE;
                                affichageMenu(Surf_fenetre_menu,imagedefond_menu,imagedetitre_menu, option_select, quitter_select);
                                SDL_UpdateWindowSurface(window_menu);
                            }
                        }else{
                            if (option_select == SDL_TRUE)
                            {
                                option_select = SDL_FALSE;
                                affichageMenu(Surf_fenetre_menu,imagedefond_menu,imagedetitre_menu, option_select, quitter_select);
                                SDL_UpdateWindowSurface(window_menu);
                            }
                        }
                        if (evenement_fenetre.motion.x > 350 && evenement_fenetre.motion.x < 480 &&
                            evenement_fenetre.motion.y > 310 && evenement_fenetre.motion.y < 350){

                            if (quitter_select == SDL_FALSE)
                            {

                                quitter_select = SDL_TRUE;
                                affichageMenu(Surf_fenetre_menu,imagedefond_menu,imagedetitre_menu, option_select, quitter_select);
                                SDL_UpdateWindowSurface(window_menu);
                            }
                        }else{
                            if (quitter_select == SDL_TRUE)
                            {
                                quitter_select = SDL_FALSE;
                                affichageMenu(Surf_fenetre_menu,imagedefond_menu,imagedetitre_menu, option_select, quitter_select);
                                SDL_UpdateWindowSurface(window_menu);
                            }
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
    SDL_DestroyWindow(window_menu);
    return 0;

}

void SDL_ExitWithError(const char *message)
{
    SDL_Log("ERREUR : %s > %s\n", message, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}

