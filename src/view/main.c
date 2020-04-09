#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "viewUtils.h" 


#define WIDTH 800
#define HEIGHT 450

int fenetreMenu(void);
int fenetreJeu(void);
int affichageMenu(SDL_Surface *Surf_fenetre_menu , SDL_Surface *imagedefond_menu,SDL_Surface *imagedetitre_menu,SDL_bool option_select,SDL_bool quitter_select);
int affichageChoix(SDL_Surface *Surf_fenetre_menu , SDL_Surface *imagedefond_menu,int choixChanson);

int ZoneJeu(char path[1][40]);

int main(int argc, char *argv[])
{

    //Lancement SDL
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
        SDL_ExitWithError("Initialisation SDL");

    if (fenetreMenu() != 0)
    {
        SDL_ExitWithError("Erreur fenetre");
    }
    SDL_Quit();
    
    return EXIT_SUCCESS;
}
/**
 * @brief      
 * Fonction d'affichage de la fenêtre de choix de musique avant de jouer
 *
 * @param      Surf_fenetre_menu  Surface de la fenêtre
 * @param      imagedefond_menu   Surface de l'image de fond de la fenêtre
 * @param[in]  choixChanson       Changement de séléction de la musique [0=pas de séléction, 1 et 2 chanson 1 ou 2]
 *
 * @return     0 si ok
 */

int affichageChoix(SDL_Surface *Surf_fenetre_menu , SDL_Surface *imagedefond_menu,int choixChanson){ 

    SDL_Surface *titre = NULL;


    SDL_BlitSurface(imagedefond_menu,NULL,Surf_fenetre_menu,NULL);

    SDL_Rect position_txt_titre ={50,20,0,0};
    titre = SDL_LoadBMP("../ressources/img/text/setlist_black.bmp");
    SDL_BlitSurface(titre, NULL, Surf_fenetre_menu,&position_txt_titre); //Fusion des messages et surfaces pour l'affichage

    SDL_Surface *imagetexte_adele=NULL;
    SDL_Surface *imagetexte_wagner=NULL;
    SDL_Surface *imagetexte_nirvana=NULL;

    SDL_Rect position_txt_chanson1 ={20,100,0,0};

        
    if (choixChanson != 1)
    {
        imagetexte_wagner = SDL_LoadBMP("../ressources/img/text/wagner_black.bmp"); //on change la police de manière conditionnel
    }else{
        imagetexte_wagner = SDL_LoadBMP("../ressources/img/text/wagner_red.bmp");
    }
    SDL_BlitSurface(imagetexte_wagner, NULL, Surf_fenetre_menu,&position_txt_chanson1); 

    SDL_Rect position_txt_chanson2 ={20,200,0,0};
    if (choixChanson != 2)
    {
        imagetexte_adele = SDL_LoadBMP("../ressources/img/text/adele_black.bmp");
    }else{
        imagetexte_adele = SDL_LoadBMP("../ressources/img/text/adele_red.bmp");
    }
    SDL_BlitSurface(imagetexte_adele, NULL, Surf_fenetre_menu,&position_txt_chanson2);

    SDL_Rect position_txt_chanson3 ={20,300,0,0};
    if (choixChanson != 3)
    {
        imagetexte_nirvana = SDL_LoadBMP("../ressources/img/text/nirvana_black.bmp");
    }else{
        imagetexte_nirvana = SDL_LoadBMP("../ressources/img/text/nirvana_red.bmp");
    }
    SDL_BlitSurface(imagetexte_nirvana, NULL, Surf_fenetre_menu,&position_txt_chanson3);

    SDL_FreeSurface(titre);
    SDL_FreeSurface(imagetexte_adele);
    SDL_FreeSurface(imagetexte_nirvana);
    SDL_FreeSurface(imagetexte_wagner);

    return 0;
}


/**
 * @brief      Fonction qui régie le fonctionnement de la fenêtre de choix
 *
 * @return     0 si ok
 */
int fenetreChoix(){
    SDL_Window *window_choix = NULL;
    SDL_bool fenetre_lance = SDL_TRUE;
    int choixChanson = 0;


    window_choix = SDL_CreateWindow("HérosDeLaGuitare2i - choix",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WIDTH,HEIGHT,0);
    if(window_choix == NULL)
        SDL_ExitWithError("Creation fenetre echouee");

    SDL_Surface *Surf_fenetre_choix=NULL;
    SDL_Surface *imagedefond_choix=NULL;

    imagedefond_choix = SDL_LoadBMP("../ressources/img/old-parchment.bmp");
    if (imagedefond_choix == NULL)
    {
        printf("Image non chargée\n");
    }
    Surf_fenetre_choix = SDL_GetWindowSurface(window_choix);
    
    affichageChoix(Surf_fenetre_choix,imagedefond_choix, choixChanson); //on affiche une première fois la fenêtre (i.e. on charge les éléments sur la surface)

    SDL_UpdateWindowSurface(window_choix); //puis on met à jour la fenêtre avec ses surfaces associées

    char titreChanson[1][40];

    
    
    while(fenetre_lance){
        

        SDL_Event evenement_fenetre;

        while(SDL_PollEvent(&evenement_fenetre)){
            switch(evenement_fenetre.type){
                case SDL_MOUSEBUTTONDOWN:
                    printf("%d / %d\n",evenement_fenetre.button.x,evenement_fenetre.button.y ); // Si la première musiqe est séléctionnée
                    if (evenement_fenetre.button.x > 20 && evenement_fenetre.button.x < 575 &&
                        evenement_fenetre.button.y > 110 && evenement_fenetre.button.y < 150){
                        strcpy(titreChanson[0],"../ressources/songs/wedding_march.txt");
                        SDL_FreeSurface(Surf_fenetre_choix);
                        SDL_FreeSurface(imagedefond_choix);
                        SDL_DestroyWindow(window_choix);
                        fenetre_lance = SDL_FALSE;// on ferme la fenêtre et lance le jeu sur cette musique
                        ZoneJeu(titreChanson); //le chemin de la musique

                    }
                    if (evenement_fenetre.button.x > 20 && evenement_fenetre.button.x < 370 &&
                        evenement_fenetre.button.y > 200 && evenement_fenetre.button.y < 260){
                        SDL_FreeSurface(Surf_fenetre_choix);
                        SDL_FreeSurface(imagedefond_choix);
                        strcpy(titreChanson[0],"../ressources/songs/hello.txt");
                        SDL_DestroyWindow(window_choix);
                        fenetre_lance = SDL_FALSE;// on ferme la fenêtre et lance le jeu sur cette musique
                        ZoneJeu(titreChanson); //le chemin de la musique

                    }
                    if (evenement_fenetre.button.x > 20 && evenement_fenetre.button.x < 690 &&
                        evenement_fenetre.button.y > 300 && evenement_fenetre.button.y < 360){
                        strcpy(titreChanson[0],"../ressources/songs/nirvana.txt");
                        SDL_FreeSurface(Surf_fenetre_choix);
                        SDL_FreeSurface(imagedefond_choix);
                        SDL_DestroyWindow(window_choix);
                        fenetre_lance = SDL_FALSE;// on ferme la fenêtre et lance le jeu sur cette musique
                        ZoneJeu(titreChanson); //le chemin de la musique

                    }
                    break;

                case SDL_MOUSEMOTION:
                        
                        if (evenement_fenetre.motion.x > 20 && evenement_fenetre.motion.x < 575 && //on regarde si la souris est au dessus d'un des textes
                            evenement_fenetre.motion.y > 110 && evenement_fenetre.motion.y < 150){

                            if (choixChanson !=1) //si elle est déjà affichée comme séléctionnée, il n'est pas nécessaire de changer l'affichage
                            {
                                choixChanson = 1;
                                affichageChoix(Surf_fenetre_choix,imagedefond_choix, choixChanson); //si oui on l'affiche dans une autre police
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
                        if (evenement_fenetre.motion.x > 20 && evenement_fenetre.motion.x < 370 &&
                            evenement_fenetre.motion.y > 200 && evenement_fenetre.motion.y < 260){

                            if (choixChanson !=2)
                            {
                                choixChanson = 2;
                                affichageChoix(Surf_fenetre_choix,imagedefond_choix, choixChanson);
                                SDL_UpdateWindowSurface(window_choix);
                            }
                        }else{
                            if (choixChanson == 2)
                            {
                                choixChanson = 0;
                                affichageChoix(Surf_fenetre_choix,imagedefond_choix, choixChanson);
                                SDL_UpdateWindowSurface(window_choix);
                            }
                        }
                        if (evenement_fenetre.motion.x > 20 && evenement_fenetre.motion.x < 690 && //on regarde si la souris est au dessus d'un des textes
                            evenement_fenetre.motion.y > 300 && evenement_fenetre.motion.y < 360){

                            if (choixChanson !=3) //si elle est déjà affichée comme séléctionnée, il n'est pas nécessaire de changer l'affichage
                            {
                                choixChanson = 3;
                                affichageChoix(Surf_fenetre_choix,imagedefond_choix, choixChanson); //si oui on l'affiche dans une autre police
                                SDL_UpdateWindowSurface(window_choix);
                            }
                        }else{
                            if (choixChanson == 3)
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

/**
 * @brief      Fonction d'affichage de la fenêtre de menu
 *
 * @param      Surf_fenetre_menu  surface de la fenêtre
 * @param      imagedefond_menu   surface de l'image de fond
 * @param      imagedetitre_menu  surface de l'image du titre
 * @param[in]  option_select      booleen si le choix est a afficher comme séléctionné
 * @param[in]  quitter_select     booleen si le choix est a afficher comme séléctionné
 *
 * @return     { description_of_the_return_value }
 */
int affichageMenu(SDL_Surface *Surf_fenetre_menu , SDL_Surface *imagedefond_menu,SDL_Surface *imagedetitre_menu,SDL_bool option_select,SDL_bool quitter_select){

    SDL_BlitSurface(imagedefond_menu,NULL,Surf_fenetre_menu,NULL);
    SDL_Rect position_txt_title ={(WIDTH-553)/2,20,0,0};
    
    SDL_BlitSurface(imagedetitre_menu, NULL, Surf_fenetre_menu,&position_txt_title);

    SDL_Rect position_txt_option ={(WIDTH-330)/2,150,0,0};
    SDL_Surface *imagetexte_choix=NULL;
    SDL_Surface *imagetexte_quitter=NULL;
        
    if (option_select == SDL_FALSE) //on affiche conditionnellement le texte, si il est séléctionné ou non 
    {
        imagetexte_choix = SDL_LoadBMP("../ressources/img/text/choix_black.bmp");
    }else{
        imagetexte_choix = SDL_LoadBMP("../ressources/img/text/choix_yellow.bmp");
    }
    SDL_BlitSurface(imagetexte_choix, NULL, Surf_fenetre_menu,&position_txt_option);

    SDL_Rect position_txt_quitter ={(WIDTH-170)/2,300,0,0};
    if (quitter_select == SDL_FALSE)
    {
        imagetexte_quitter = SDL_LoadBMP("../ressources/img/text/quitter_black.bmp");
    }else{
        imagetexte_quitter = SDL_LoadBMP("../ressources/img/text/quitter_yellow.bmp");
    }
    SDL_BlitSurface(imagetexte_quitter, NULL, Surf_fenetre_menu,&position_txt_quitter);

    SDL_FreeSurface(imagetexte_quitter);
    SDL_FreeSurface(imagetexte_choix);

    return 0;
}

/**
 * @brief      Fenêtre qui gère le menu 
 *
 * @return     0 si ok
 */
int fenetreMenu(){
    SDL_Window *window_menu = NULL;
    SDL_bool fenetre_lance = SDL_TRUE;

    //création fenêtre
    window_menu = SDL_CreateWindow("HérosDeLaGuitare2i",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WIDTH,HEIGHT,0);

    if(window_menu == NULL)
        SDL_ExitWithError("Creation fenetre echouee");

    
    SDL_bool option_select = SDL_FALSE; //booleen indiquant si l'option est survolée
    SDL_bool quitter_select = SDL_FALSE;
    


    SDL_Surface *Surf_fenetre_menu=NULL;
    SDL_Surface *imagedefond_menu=NULL;
    SDL_Surface *imagedetitre_menu=NULL;

    imagedefond_menu = SDL_LoadBMP("../ressources/img/fond_fenetre2.bmp");
    if (imagedefond_menu == NULL)
    {
        printf("Image non chargée\n");
    }
    Surf_fenetre_menu = SDL_GetWindowSurface(window_menu);

    imagedetitre_menu = SDL_LoadBMP("../ressources/img/title.bmp");


    
    affichageMenu(Surf_fenetre_menu,imagedefond_menu,imagedetitre_menu, option_select, quitter_select); //on met a jour les surfaces d'affichage

    SDL_UpdateWindowSurface(window_menu); //puis màj de la fenêtre d'affichage

    

    
    
    while(fenetre_lance){
        

        SDL_Event evenement_fenetre;

        while(SDL_PollEvent(&evenement_fenetre)){
            switch(evenement_fenetre.type){ //si l'on clique sur une des option, on réagit en conseéquence
                case SDL_MOUSEBUTTONDOWN:
                    printf("%d / %d\n",evenement_fenetre.button.x,evenement_fenetre.button.y );
                    if (evenement_fenetre.button.x > 235 && evenement_fenetre.button.x < 565 &&
                        evenement_fenetre.button.y > 155 && evenement_fenetre.button.y < 210){
                        SDL_FreeSurface(imagedefond_menu);
                        SDL_FreeSurface(Surf_fenetre_menu);
                        SDL_FreeSurface(imagedetitre_menu);
                        SDL_DestroyWindow(window_menu);
                        fenetre_lance = SDL_FALSE;
                        fenetreChoix(); //destruction fenêtre et ouverture de l'autre fenêtre
                    }
                    if (evenement_fenetre.button.x > 315 && evenement_fenetre.button.x < 490 &&
                            evenement_fenetre.button.y > 300 && evenement_fenetre.button.y < 360){
                        fenetre_lance = SDL_FALSE; //quitte le programme
                    }
                    break;

                case SDL_MOUSEMOTION:
                        if (evenement_fenetre.motion.x > 235 && evenement_fenetre.motion.x < 565 && 
                            evenement_fenetre.motion.y > 155 && evenement_fenetre.motion.y < 210){

                            if (option_select == SDL_FALSE) //Si oui et qu'il n'est pas déjà afficher en survolé, alors on change pour le mettre en survolé
                            {
                                option_select = SDL_TRUE;
                                affichageMenu(Surf_fenetre_menu,imagedefond_menu,imagedetitre_menu, option_select, quitter_select); //Puis on met à jour les surfaces
                                SDL_UpdateWindowSurface(window_menu); //et on met à jour l'écran affiché
                            }
                        }else{
                            if (option_select == SDL_TRUE)
                            {
                                option_select = SDL_FALSE;
                                affichageMenu(Surf_fenetre_menu,imagedefond_menu,imagedetitre_menu, option_select, quitter_select);
                                SDL_UpdateWindowSurface(window_menu);
                            }
                        }
                        if (evenement_fenetre.motion.x > 315 && evenement_fenetre.motion.x < 490 &&
                            evenement_fenetre.motion.y > 300 && evenement_fenetre.motion.y < 360){

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