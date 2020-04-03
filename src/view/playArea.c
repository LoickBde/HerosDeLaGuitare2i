#include "viewUtils.h" 

void createTestRect(SDL_Rect myRects[]);  //Test a supprimer

int main(int argc, char *argv[])
{
    SDL_Window *window = NULL; //Pointeur sur la fenêtre
    SDL_Renderer *renderer = NULL; //Pointeur sur le renderer
    SDL_Texture *texture_foreground, *texture_background, *texture_gameBoard = NULL; //Texture pour les cordes, l'image de fond et les deux en un
    SDL_Texture *texture_musicNote; //Texture contenant le curseur a déssiner
    SDL_bool prgm_running = SDL_TRUE; 
    SDL_Rect myRects[NB_NOTE];  //Pour test, a supprimer

    initSDLbasics(&window, &renderer, "Zone de jeu"); //Initialise les bases de la sdl (fenetre, renderer)

    initTexturesGameBoard(renderer, &texture_foreground, &texture_background, &texture_gameBoard); 
    
    createGameBoard(renderer, texture_foreground, texture_background, &texture_gameBoard); //Mise en place de la zone de jeu
    
    SDL_RenderPresent(renderer); //Maj de l'affichage 
    
    SDL_DestroyTexture(texture_foreground); //Détruit les textures qui ne servent plus
    SDL_DestroyTexture(texture_background); 

    createMusicNote(renderer, &texture_musicNote); //Crée la texture modèle a copié pour les notes

    //---- TEST ----//
    unsigned int frameLimit; 
    SDL_bool isFinished = SDL_FALSE; 

    createTestRect(myRects);

    if(SDL_SetRenderTarget(renderer, NULL) != 0) //Renderer rendu cible 
         SDL_ExitWithError("Erreur change render target");
    while(!isFinished)
    {
        frameLimit = SDL_GetTicks() + FPS_LIMIT;

        if(SDL_RenderClear(renderer) != 0)
                SDL_ExitWithError("Pb render clear"); 
        if(SDL_RenderCopy(renderer, texture_gameBoard, NULL, NULL) != 0)
                SDL_ExitWithError("Pb render copy");
        
        isFinished = SDL_TRUE; 
        
        for(int i=0; i<NB_NOTE; i++)
        {
            if(myRects[i].y <= HEIGHT)
            {
                if(isFinished) //Gestion du flag facon ksos
                    isFinished = SDL_FALSE; 

                if(SDL_RenderCopy(renderer, texture_musicNote, NULL, &myRects[i]) != 0)
                    SDL_ExitWithError("Pb render copy");
                
                myRects[i].y += SPEED_MOVEMENT; 
            }
        }

        SDL_limitFPS(frameLimit);
        SDL_RenderPresent(renderer); 
        frameLimit = SDL_GetTicks() + FPS_LIMIT;
    }
    //---- TEST ----//
    
    while(prgm_running)
    {
        SDL_Event event; 
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT : 
                    prgm_running = SDL_FALSE; 
                    break; 
                default :
                    break; 
            }
        }
    }
    
    SDL_DestroyTexture(texture_gameBoard); //Détruit les textures restantes
    SDL_DestroyRenderer(renderer); //Detruit le render
    SDL_DestroyWindow(window); //Détruit la fenetre
    SDL_Quit(); //Quitte la sdl

    return EXIT_SUCCESS;
}

void createTestRect(SDL_Rect myRects[]){ //Pour test, a supprimer
    SDL_Rect rectTest = {0,0,MUSIC_NOTE_SIZE, MUSIC_NOTE_SIZE}; //Initialise la zone a dessiner
    int currentString = 0; //Permet de stocker au bon endroit

    for(int i=0; i<NB_STRING; i++) //Pour chaque corde on veut NB_NOTE_STRING de note
    {
        rectTest.x = stringPosition[i]-(MUSIC_NOTE_SIZE/2); //On donne la position de la corde en x 
        rectTest.y = 0; //Position en y de la note sur la corde
        for(int j=0; j<NB_NOTE_STRING; j++) //X notes par corde
        {
            myRects[currentString] = rectTest;
            rectTest.y = rectTest.y + 35; 
            currentString++; 
        }
    }
}