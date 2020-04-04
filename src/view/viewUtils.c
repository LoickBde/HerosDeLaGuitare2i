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
    int sizeGuitar = WIDTH - SIZE_SIDE*2; 
    int sizeGap = sizeGuitar/nbDiv; 

    if(SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE) != 0) //Couleur blanche
        SDL_ExitWithError("Erreur mise en place de la coueleur blanche");

    //Dessine les contours
    //Render, x1, y1, x2, y2
    if(SDL_RenderDrawLine(renderer, SIZE_SIDE, 0, SIZE_SIDE, HEIGHT) != 0) //Bord gauche
        SDL_ExitWithError("Erreur dessin ligne bord gauche");
    if(SDL_RenderDrawLine(renderer, WIDTH-SIZE_SIDE, 0, WIDTH-SIZE_SIDE, HEIGHT) != 0) //Bord droit
        SDL_ExitWithError("Erreur dessin ligne bord droit");
    if(SDL_RenderDrawLine(renderer, SIZE_SIDE, HEIGHT-SIZE_BOT, WIDTH-SIZE_SIDE, HEIGHT-SIZE_BOT) != 0) //Ligne du bas
        SDL_ExitWithError("Erreur dessin ligne ligne du bas");  

    //Dessine les cordes
    int i = 0; 
    int currentX = SIZE_SIDE + sizeGap; 
    while(currentX < sizeGuitar+SIZE_SIDE)
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

//Pour initialiser les notes
void initNotesTest(SDL_Rect myRects[]){ //Pour test, a supprimer
    SDL_Rect rectTest = {0,0,MUSIC_NOTE_SIZE, MUSIC_NOTE_SIZE}; //Initialise la zone a dessiner
    int currentString = 0; //Permet de stocker au bon endroit

    //Version chargement corde par corde
   /*  for(int i=0; i<NB_STRING; i++) //Pour chaque corde on veut NB_NOTE_STRING de note
    {
        rectTest.x = stringPosition[i]-(MUSIC_NOTE_SIZE/2); //On donne la position de la corde en x 
        rectTest.y = -150; //Position en y de la note sur la corde
        for(int j=0; j<NB_NOTE_STRING; j++) //X notes par corde
        {
            myRects[currentString] = rectTest;
            rectTest.y = rectTest.y + 50; 
            currentString++; 
        }
    } */

    //Chargement chronolologie verticale
    rectTest.y = -150; //Position en y de la note sur la corde
    for(int j=0; j<NB_NOTE_STRING; j++) //X notes par corde
    {
        for(int i=0; i<NB_STRING; i++) //Pour chaque corde on veut NB_NOTE_STRING de note
        {
            rectTest.x = stringPosition[i]-(MUSIC_NOTE_SIZE/2); //On donne la position de la corde en x 
            myRects[currentString] = rectTest;
            rectTest.y = rectTest.y + 50; 
            currentString++; 
        }
    }
}

//Initialise les notes a partir d'un fichier texte passé en argument
void initNotesFromFile(const char* path, SDL_Rect myRects[])
{
    SDL_Rect rectToDraw = {0,0,MUSIC_NOTE_SIZE, MUSIC_NOTE_SIZE}; //Initialise la zone a dessiner
    FILE *fic = fopen(path, "r");
    char line[MAX_BUFF];  
    int flag = 0, i=0; 

    if(fic == NULL)
        SDL_ExitWithError("Impossible d'ouvrir le fichier de musique"); 
    
    while (fgets (line, MAX_BUFF, fic) != NULL ) //Ligne par ligne
    {
        if(!flag)
        {
            rectToDraw.x = stringPosition[atoi(line)-1]-(MUSIC_NOTE_SIZE/2); //On donne la position de la corde en x 
            flag=1; 
        }
        else
        {
            rectToDraw.y = atoi(line); 
            myRects[i]= rectToDraw; 
            i++; 
            flag=0; 
        }
        
    }
    fclose(fic); 
}

//Permet de gérer le définlement des notes 
void animation(SDL_Renderer *renderer, SDL_Texture *texture_gameBoard, SDL_Texture *texture_musicNote, SDL_Rect myRects[], SDL_bool *songFinished)
{
    unsigned int frameLimit; //Pour les fps, synchro

    frameLimit = SDL_GetTicks() + FPS_LIMIT; //Limites pour fps

    if(SDL_RenderClear(renderer) != 0)  //Nettoie le render
            SDL_ExitWithError("Pb render clear"); 
    if(SDL_RenderCopy(renderer, texture_gameBoard, NULL, NULL) != 0) //Copie le plateau de jeu
            SDL_ExitWithError("Pb render copy");
    
    *songFinished = SDL_TRUE; //Flag
    
    for(int i=0; i<NB_NOTE; i++) //Pour toutes les notes
    {
        if(myRects[i].y <= HEIGHT) //On regarde si elles valent le coup d'etre affichée
        {
            if(*songFinished) //Gestion du flag 
                *songFinished = SDL_FALSE; 

            if(SDL_RenderCopy(renderer, texture_musicNote, NULL, &myRects[i]) != 0) //Si oui on copie 
                SDL_ExitWithError("Pb render copy");
            
            myRects[i].y += SPEED_MOVEMENT; //On modifie la coordonnée
        }
    }

    SDL_limitFPS(frameLimit); //Limitation des fps
    
    SDL_RenderPresent(renderer); //On actualise
    
    frameLimit = SDL_GetTicks() + FPS_LIMIT; //Fps synchro
}

//Permet de savoir si la note est dans la bonne zone pour la valider (a optimiser)
void checkNoteArea(int cooX, SDL_Rect myRects[])
{
    SDL_Rect area = {cooX-(MUSIC_NOTE_SIZE/2), HEIGHT-SIZE_BOT-(MUSIC_NOTE_SIZE/2), MUSIC_NOTE_SIZE, MUSIC_NOTE_SIZE}; //Crée un rectangle de la bonne taille au bon endroit
    SDL_Rect closestNote = {-1, 0, 0, 0}; //Init d'un rectangle qui permet de sauvegarder la note la plus proche
    SDL_Rect intersectZone = {0,0,0,0}; 
    int closestNoteIndex = -1; 

    for(int i=0; i<NB_NOTE; i++) //Pour toute les notes
    {
        if(myRects[i].x == cooX-(MUSIC_NOTE_SIZE/2) && myRects[i].y+MUSIC_NOTE_SIZE > 0 && myRects[i].y < HEIGHT) //Si sur la bonne corde, et dans l'écran
        {
            if(closestNote.x == -1 || closestNote.y < myRects[i].y)
            {
                closestNote = myRects[i]; //On garde la note la plus proche
                closestNoteIndex = i; //Et son index
            }
        }
    }

    if(SDL_IntersectRect(&area, &closestNote, &intersectZone) && closestNote.y+MUSIC_NOTE_SIZE >= HEIGHT-SIZE_BOT) //On check si la note est dans la zone
    {
        if(intersectZone.h >= 20)
        {
            printf("Taille d'intersection: %d. Parfait !\n", intersectZone.h); 
            updateScore(intersectZone.h); 
            printf("Score : %d\n", score); 
        }
        else
        {
            printf("Taille d'intersection: %d. Bien !\n", intersectZone.h); 
            updateScore(intersectZone.h); 
            printf("Score : %d\n", score); 
        }
    }
    else 
    {
        printf("Taille d'intersection: 0. Raté !\n");
        printf("Score : %d\n", score); 
    }
    
    if(closestNoteIndex != -1) //Permet de ne plus afficher la note jouée
        myRects[closestNoteIndex].y = HEIGHT + 1;
} 

void updateScore(int points)
{
    score += points*4; 
}