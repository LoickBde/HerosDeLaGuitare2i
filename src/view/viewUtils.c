#include "viewUtils.h" 

//Gére les erreurs
void SDL_ExitWithError(const char *message)
{
    SDL_Log("ERREUR : %s > %s\n", message, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}

//Init SDL ainsi qu'une fenetre et un renderer
void initSDLbasics(SDL_Window **window, SDL_Renderer **renderer, const char *windowTitle)
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0) //Init la video de la sdl2
        SDL_ExitWithError("Erreur init SDL2");
    
    //Titre, pos x, pos y, taille x, taille y, options fenetre
    *window = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN );
    if(*window == NULL)
        SDL_ExitWithError("Erreur création fenêtre");

    //Fenetre a associe, pilote (-1 = premier qui correspond), méthode pour afficher le rendu
    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED); 
    if(*renderer == NULL)
        SDL_ExitWithError("Erreur création renderer");
    
    if(SDL_RenderClear(*renderer) != 0)
        SDL_ExitWithError("Erreur renderer clear");
}

SDL_Texture *loadImage(SDL_Renderer *renderer, const char *path)
{
    SDL_Surface *surface_img = NULL; //Pointeur sur la surface temporaire (pour charger une image)
    SDL_Texture *texture_img = NULL; //Pointeur sur la texture contenat l'image

    surface_img = SDL_LoadBMP(path); //Charge l'image 
    if(surface_img == NULL)
        SDL_ExitWithError("Erreur création surface a partir d'une image");   
    texture_img = SDL_CreateTextureFromSurface(renderer, surface_img); //Crée une texture a partir de l'image = texture contenat l'image
    if(texture_img == NULL)
        SDL_ExitWithError("Erreur création texture à partir d'images"); 
    SDL_FreeSurface(surface_img); //On free la surface qui ne va plus nous servir pour la suite

    return texture_img; 
}

void initTexturesGameBoard(SDL_Renderer *renderer, SDL_Texture **texture_foreground, SDL_Texture **texture_background, SDL_Texture **texture_gameBoard)
{
    *texture_foreground = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, 
                            SDL_TEXTUREACCESS_TARGET, WIDTH, HEIGHT);
    if(*texture_foreground == NULL)
        SDL_ExitWithError("Erreur création texture");
    *texture_background = loadImage(renderer, "../ressources/img/fond_jeu.bmp");  //Charge l'image dans la texture
    *texture_gameBoard = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, 
                            SDL_TEXTUREACCESS_TARGET, WIDTH, HEIGHT);
    if(texture_gameBoard == NULL)
        SDL_ExitWithError("Erreur création texture");
}

//Dessine le tableau de jeu
void drawGameBoard(SDL_Renderer *renderer)
{
    int nbDiv = NB_STRING+1;
    int sizeSide = 150; 
    int sizeBottom = 80; 
    int sizeGuitar = WIDTH - sizeSide*2; 
    int sizeGap = sizeGuitar/nbDiv; 

    if(SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE) != 0) //Couleur blanche
        SDL_ExitWithError("Erreur mise en place de la coueleur blanche");

    //Dessine les contours
    //Render, x1, y1, x2, y2
    if(SDL_RenderDrawLine(renderer, sizeSide, 0, sizeSide, HEIGHT) != 0) //Bord gauche
        SDL_ExitWithError("Erreur dessin ligne bord gauche");
    if(SDL_RenderDrawLine(renderer, WIDTH-sizeSide, 0, WIDTH-sizeSide, HEIGHT) != 0) //Bord droit
        SDL_ExitWithError("Erreur dessin ligne bord droit");
    if(SDL_RenderDrawLine(renderer, sizeSide, HEIGHT-sizeBottom, WIDTH-sizeSide, HEIGHT-sizeBottom) != 0) //Ligne du bas
        SDL_ExitWithError("Erreur dessin ligne ligne du bas");  

    //Dessine les cordes
    int i = 0; 
    int currentX = sizeSide + sizeGap; 
    while(currentX < sizeGuitar+sizeSide)
    {      
        if(SDL_RenderDrawLine(renderer, currentX, 0, currentX, HEIGHT) != 0) //Chaque corde
            SDL_ExitWithError("Erreur dessin cordes guitare");
        stringPosition[i]=currentX; 
        i++; 
        currentX+= sizeGap; 
    }
}

void createGameBoard(SDL_Renderer *renderer, SDL_Texture *texture_foreground, SDL_Texture *texture_background, SDL_Texture **texture_gameBoard)
{    
    if(SDL_SetRenderTarget(renderer, texture_foreground) != 0) //Texture rendu cible 
         SDL_ExitWithError("Erreur change render target");
    if(SDL_RenderClear(renderer) != 0) //Clear le foreground
        SDL_ExitWithError("Erreur clear renderer");
    if(SDL_RenderCopy(renderer, texture_background, NULL, NULL) != 0)
        SDL_ExitWithError("Erreur rendercopy");; 
    drawGameBoard(renderer);//Dessin sur la texture
    if(SDL_SetRenderTarget(renderer, *texture_gameBoard) != 0) // La cible de rendu est la texture gameBoard
        SDL_ExitWithError("Erreur change render target"); 
    if(SDL_RenderCopy(renderer, texture_foreground, NULL, NULL) != 0)
        SDL_ExitWithError("Erreur rendercopy");;  
    if(SDL_SetRenderTarget(renderer, NULL) != 0) // La cible de rendu est de nouveau le renderer
        SDL_ExitWithError("Erreur change render target"); 
    if(SDL_RenderCopy(renderer, *texture_gameBoard, NULL, NULL) != 0)
        SDL_ExitWithError("Erreur rendercopy");;  
}

void createMusicNote(SDL_Renderer *renderer, SDL_Texture **texture_musicNote) //Crée le modele du petit curseur mobile
{
    SDL_Rect musicNote = {0,0,MUSIC_NOTE_SIZE, MUSIC_NOTE_SIZE}; //Le carré a dessiner

    *texture_musicNote = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, 
                            SDL_TEXTUREACCESS_TARGET, MUSIC_NOTE_SIZE, MUSIC_NOTE_SIZE);
    if(*texture_musicNote== NULL)
        SDL_ExitWithError("Erreur création texture");

    if(SDL_SetRenderTarget(renderer, *texture_musicNote) != 0) //Texture rendu cible 
        SDL_ExitWithError("Erreur change render target");

    if(SDL_SetRenderDrawColor(renderer,0,0,0, SDL_ALPHA_OPAQUE) != 0) //Nettoie la texture
        SDL_ExitWithError("Erreur chgt couleur"); 
    if(SDL_RenderClear(renderer) != 0)
        SDL_ExitWithError("Erreur clear"); 

    if(SDL_SetRenderDrawColor(renderer,255,255,255, SDL_ALPHA_OPAQUE) != 0) //Dessine le modele sur la texture
        SDL_ExitWithError("Erreur chgt couleur"); 
    if(SDL_RenderFillRect(renderer, &musicNote) != 0)
        SDL_ExitWithError("Erreur dessin rectangle");

     if(SDL_SetRenderTarget(renderer, NULL) != 0) //Renderer rendu cible 
         SDL_ExitWithError("Erreur change render target");
}

//Permet de gérer les FPS
void SDL_limitFPS(unsigned int limit)
{
    unsigned int ticks = SDL_GetTicks(); 

    if(limit < ticks) //Retard
        return; 
    else if(limit > ticks + FPS_LIMIT) //Avance par rapport a la limit de fps
        SDL_Delay(FPS_LIMIT);
    else //Avance par rapport aux ticks
        SDL_Delay(limit - ticks); 
    return; 
}