#include "viewUtils.h" 

int main(int argc, char *argv[])
{
    SDL_Window *window = NULL; //Pointeur sur la fenêtre
    SDL_Renderer *renderer = NULL; //Pointeur sur le renderer
    SDL_Texture *texture_foreground, *texture_background, *texture_gameBoard = NULL; //Texture pour les cordes, l'image de fond et les deux en un
    SDL_Texture *texture_musicNote; //Texture contenant le curseur a déssiner
    SDL_bool prgm_running = SDL_TRUE; 
    SDL_bool songFinished = SDL_FALSE; 
    SDL_Rect myRects[NB_NOTE];  //Pour test, a supprimer

    initSDLbasics(&window, &renderer, "Zone de jeu"); //Initialise les bases de la sdl (fenetre, renderer)

    initTexturesGameBoard(renderer, &texture_foreground, &texture_background, &texture_gameBoard); 
    
    createGameBoard(renderer, texture_foreground, texture_background, &texture_gameBoard); //Mise en place de la zone de jeu
    
    SDL_RenderPresent(renderer); //Maj de l'affichage 
    
    SDL_DestroyTexture(texture_foreground); //Détruit les textures qui ne servent plus
    SDL_DestroyTexture(texture_background); 

    createMusicNote(renderer, &texture_musicNote); //Crée la texture modèle a copié pour les notes

    initNotesTest(myRects); //Initialise le placement des notes

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
            else if(event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.scancode)
                {
                    case SDL_SCANCODE_S:
                        puts("S appuyé");
                        break;
                    case SDL_SCANCODE_D:
                        puts("D appuyé");
                        break;
                    case SDL_SCANCODE_F:
                        puts("F appuyé");
                        break;
                    case SDL_SCANCODE_G:
                        puts("G appuyé"); 
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
    SDL_Quit(); //Quitte la sdl

    return EXIT_SUCCESS;
}