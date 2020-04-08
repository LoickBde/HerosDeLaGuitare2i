#include "viewUtils.h" 

int ZoneJeu(char path[1][40])
{
    SDL_Window *window = NULL; //Pointeur sur la fenêtre
    SDL_Renderer *renderer = NULL; //Pointeur sur le renderer
    SDL_Texture *texture_foreground, *texture_background, *texture_gameBoard = NULL; //Texture pour les cordes, l'image de fond et les deux en un
    SDL_Texture *texture_musicNote; //Texture contenant le curseur a déssiner
    SDL_bool prgm_running = SDL_TRUE; 
    SDL_bool songFinished = SDL_FALSE; 
    SDL_Rect myRects[NB_NOTE];  //Pour test, a supprimer


    initSDLbasics(&window, &renderer, "Zone de jeu"); //Initialise les bases de la sdl (fenetre, renderer)
    initSegments();
    initMatrix();
    initMusic();

    initTexturesGameBoard(renderer, &texture_foreground, &texture_background, &texture_gameBoard); 
    
    createGameBoard(renderer, texture_foreground, texture_background, &texture_gameBoard); //Mise en place de la zone de jeu
    
    SDL_RenderPresent(renderer); //Maj de l'affichage 
    
    SDL_DestroyTexture(texture_foreground); //Détruit les textures qui ne servent plus
    SDL_DestroyTexture(texture_background); 

    createMusicNote(renderer, &texture_musicNote); //Crée la texture modèle a copié pour les notes

   // initNotesTest(myRects); //Initialise le placement des notes version test
    printf("TEST\n");
    printf("%s\n",path[0] );
    initNotesFromFile(path[0], myRects); //Initialise le placement des notes depuis un fichier txt
    score = 0; //Initialise le score 

    if(SDL_SetRenderTarget(renderer, NULL) != 0) //Renderer rendu cible 
         SDL_ExitWithError("Erreur change render target");
    if(SDL_SetRenderDrawColor(renderer,0,0,0, SDL_ALPHA_OPAQUE) != 0) //Couleur noire
        SDL_ExitWithError("Erreur chgt couleur"); 
    
    while(prgm_running)
    {
        SDL_Event event; 
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
                prgm_running = SDL_FALSE; 
            else if(event.type == SDL_KEYDOWN && event.key.repeat == 0) //Clavier et empecher la repition 
            {
                switch (event.key.keysym.scancode)
                {
                    case SDL_SCANCODE_S:
                        checkNoteArea(stringPosition[0], myRects); //Corde 1
                        break;
                    case SDL_SCANCODE_D:
                        checkNoteArea(stringPosition[1], myRects); //Corde 2
                        break;
                    case SDL_SCANCODE_F:
                        checkNoteArea(stringPosition[2], myRects); //Corde 3 
                        break;
                    case SDL_SCANCODE_G:
                        checkNoteArea(stringPosition[3], myRects); //Corde 4
                        break;
                }
            }
        }
        
        if(!songFinished)
        {
            animation(renderer, texture_gameBoard, texture_musicNote, myRects, &songFinished); 
        }
    }
    
    //---- TEST ----//

    SDL_DestroyTexture(texture_musicNote); //Détruit les textures restantes
    SDL_DestroyTexture(texture_gameBoard); 
    SDL_DestroyRenderer(renderer); //Detruit le render
    SDL_DestroyWindow(window); //Détruit la fenetre
    fenetreChoix();
   // SDL_Quit(); //Quitte la sdl

    return EXIT_SUCCESS;
}