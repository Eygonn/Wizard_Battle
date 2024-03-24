#include "fonctions.h"

SDL_Surface *temp_surface;

int vrai = 1;
int direction = 0;

SDL_Texture *run_front_tex;
SDL_Texture *run_back_tex;
SDL_Texture *run_right_tex;
SDL_Texture *run_left_tex;

SDL_Texture *fond_tex;

// Texture du menu
SDL_Texture *menu_tex;
SDL_Texture *tile_verte_tex;


int initialisation(SDL_Window **fenetre, SDL_Renderer **rendu) {
    // Initialisation de la bibliothèque SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("Problème d'initialisation de la bibliothèque SDL : %s\n", SDL_GetError());
        return 0;
    }

    // Initialisation de SDL_ttf
    if (TTF_Init() != 0) {
        printf("Erreur lors de l'initialisation de SDL_ttf : %s\n", TTF_GetError());
        return 1;
    }

    // Initialisation de la SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Erreur lors de l'initialisation de la SDL : %s\n", SDL_GetError());
        return 1;
    }

    // Création de la fenêtre et du rendu
    *fenetre = SDL_CreateWindow("test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOWS_WIDTH, WINDOWS_HEIGHT, SDL_WINDOW_OPENGL);
    *rendu = SDL_CreateRenderer(*fenetre, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(*rendu, 255, 255, 255, 255);

    if (*fenetre != NULL && *rendu != NULL) {
        return 1;
    } else {
        printf("Problème de création de la fenêtre : %s\n", SDL_GetError());
        return 0;
    }
}

void chargerTextures(SDL_Renderer *rendu, SDL_Texture * tabTile[5]){
    temp_surface = SDL_LoadBMP("images/run_front.bmp");
    run_front_tex = SDL_CreateTextureFromSurface(rendu, temp_surface);
    SDL_FreeSurface(temp_surface);
    if(run_front_tex == NULL){
        printf("Erreur de chargement de l'image 'run_front': %s\n", SDL_GetError());
    }
    else printf("Chargement de l'image 'run_front' réussi\n");

    temp_surface = SDL_LoadBMP("images/run_back.bmp");
    run_back_tex = SDL_CreateTextureFromSurface(rendu, temp_surface);
    SDL_FreeSurface(temp_surface);
    if(run_back_tex == NULL){
        printf("Erreur de chargement de l'image 'run_back': %s\n", SDL_GetError());
    }
    else printf("Chargement de l'image 'run_back' réussi\n");

    temp_surface = SDL_LoadBMP("images/run_right.bmp");
    run_right_tex = SDL_CreateTextureFromSurface(rendu, temp_surface);
    SDL_FreeSurface(temp_surface);
    if(run_right_tex == NULL){
        printf("Erreur de chargement de l'image 'run_right': %s\n", SDL_GetError());
    }
    else printf("Chargement de l'image 'run_right' réussi\n");

    temp_surface = SDL_LoadBMP("images/run_left.bmp");
    run_left_tex = SDL_CreateTextureFromSurface(rendu, temp_surface);
    SDL_FreeSurface(temp_surface);
    if(run_left_tex == NULL){
        printf("Erreur de chargement de l'image 'run_left': %s\n", SDL_GetError());
    }
    else printf("Chargement de l'image 'run_left' réussi\n");

    temp_surface = IMG_Load("images/backround.png");
    fond_tex = SDL_CreateTextureFromSurface(rendu, temp_surface);
    SDL_FreeSurface(temp_surface);
    if(fond_tex == NULL){
        printf("Erreur de chargement du fond: %s\n", SDL_GetError());
    }
    else printf("Chargement du fond réussi\n");

    temp_surface = IMG_Load("images/tile1.png");
    tile_verte_tex = SDL_CreateTextureFromSurface(rendu, temp_surface);
    SDL_FreeSurface(temp_surface);
    if(fond_tex == NULL){
        printf("Erreur de chargement de la tile verte: %s\n", SDL_GetError());
    }
    else printf("Chargement de la tile verte réussi\n");

    temp_surface = SDL_LoadBMP("images/background2.bmp");
    menu_tex = SDL_CreateTextureFromSurface(rendu, temp_surface);
    if( menu_tex == NULL){
        printf("Erreur de chargement de l'image du menu: %s\n", SDL_GetError());
    }
    else printf("Chargement du fond du menu réussi\n");

    /*Tableau de texture de tiles*/
    tabInit(tabTile, rendu);
}

int fin(SDL_Window *fenetre, SDL_Renderer *rendu) {
    SDL_DestroyRenderer(rendu);
    SDL_DestroyWindow(fenetre);
    SDL_Quit();
    return 0;
}

void affichageMenuImage(SDL_Renderer *rendu){
    SDL_RenderCopy(rendu, menu_tex, 0, 0);
}


int getMousePositionDirection(SDL_Rect *pers_destination){
    int direction = BAS;
    int x_joueur = pers_destination->x;
    int y_joueur = pers_destination->y;
    int x, y;
    SDL_GetMouseState(&x, &y);
    int x_relatif, y_relatif;
    x_relatif = x - x_joueur;
    y_relatif = -(y - y_joueur);

    if (y_relatif > 0) {
        if (x_relatif > 0) {
            direction = DROITE;
        } else if (x_relatif < 0) {
            direction = BAS;
        }
    } else if (y_relatif < 0) {
        if (x_relatif > 0) {
            direction = HAUT;
        } else if (x_relatif < 0) {
            direction = GAUCHE;
        }
    } 
    return direction;
}

void actualisationSprite(int nb_sprite, int frame, int largeur, int hauteur, int direction, SDL_Rect *src, SDL_Rect *dst, SDL_Renderer *rendu){
    SDL_Texture *texSprite;
    if (direction == HAUT) { 
        texSprite = run_front_tex;
    } else if (direction == BAS) { 
        texSprite = run_back_tex;
    } else if (direction == DROITE) { 
        texSprite = run_right_tex;
    } else if (direction == GAUCHE) { 
        texSprite = run_left_tex;
    }

    src->x = (frame % nb_sprite)*largeur;
    src->y = 0;
    src->w = largeur;
    src->h = hauteur;
    dst->w = TAILLE_SPRITE_PLAYER;
    dst->h = TAILLE_SPRITE_PLAYER;

    // On affiche les sprites  :
    SDL_RenderCopy(rendu, texSprite, src, dst);
}

void action(const Uint8 *clavier, SDL_Rect *pers_destination, SDL_Rect *pers_source, int frame, int DIM_SPRITE, SDL_Renderer *rendu) {
    int direction = BAS;

    if (clavier[SDL_SCANCODE_W] && pers_destination->y > 0 ) {
        pers_destination->y -= VITESSE_JOUEUR_Y;
    }
    if (clavier[SDL_SCANCODE_S] && (pers_destination->y < WINDOWS_HEIGHT - DIM_SPRITE_PLAYER)) {
        pers_destination->y += VITESSE_JOUEUR_Y;
    }
    if (clavier[SDL_SCANCODE_A] && pers_destination->x > 0 ) {
        pers_destination->x -= VITESSE_JOUEUR_X;
    }
    if (clavier[SDL_SCANCODE_D] && (pers_destination->x < WINDOWS_WIDTH - DIM_SPRITE_PLAYER)) {
        pers_destination->x += VITESSE_JOUEUR_X;
    }

    direction = getMousePositionDirection(pers_destination);

    actualisationSprite(6, frame, DIM_SPRITE, DIM_SPRITE, direction, pers_source, pers_destination, rendu);
}

void renduFond(SDL_Renderer *rendu, SDL_Rect *cameraRect) {
    SDL_RenderCopy(rendu, fond_tex, cameraRect, NULL);
}

void updateCamera(SDL_Rect *pers_destination, SDL_Renderer *rendu, SDL_Rect *cameraRect, int tab[NB_TILE_HEIGHT][NB_TILE_WIDTH], SDL_Texture *tabTile[5]) {
    // Facteur d'interpolation linéaire
    const float interpolationFactor = 0.1f;

    // Calcul de la différence entre la position actuelle de la caméra et la position désirée du joueur
    int dx = (pers_destination->x * 2) - cameraRect->x;
    int dy = (pers_destination->y * 4) - cameraRect->y;

    // Application de l'interpolation linéaire
    cameraRect->x += (int)(dx * interpolationFactor);
    cameraRect->y += (int)(dy * interpolationFactor);

    // Correction des limites de la caméra
    if (cameraRect->x < 0) {
        cameraRect->x = 0;
    }
    if (cameraRect->y < 0) {
        cameraRect->y = 0;
    }
    if (cameraRect->y > HAUTEUR_FOND - CAMERA_HEIGHT) {
        cameraRect->y = HAUTEUR_FOND - CAMERA_HEIGHT;
    }
    if (cameraRect->x > LARGEUR_FOND - CAMERA_WIDTH) {
        cameraRect->x = LARGEUR_FOND - CAMERA_WIDTH;
    }

    // Calcul des positions des coins de la caméra
    positionJoueur_t position;

    /*ici "DIM_SPRITE_PLAYER/7" correspond à l'espace vide de la tile autour du personnage, 
    on divise par 100  car le personnage se déplace sur 1800 pixels sur l'axe x (et on divise par 120 parcequ'il se déplace sur 2160 pixels sur y)
    A terme, créer une fonction pour faire ces calculs, et remplacer les divisions par des constantes*/
    position.case_hg.casx = ((cameraRect->x - DIM_SPRITE_PLAYER/7)/ 100);
    position.case_hg.casy = ((cameraRect->y - DIM_SPRITE_PLAYER/7 )/ 120);

    position.case_hd.casx = (cameraRect->x + ((6/7)*DIM_SPRITE_PLAYER)) / 100;
    position.case_hd.casy = ((cameraRect->y - DIM_SPRITE_PLAYER/7 )/ 120);

    position.case_bg.casx = ((cameraRect->x - DIM_SPRITE_PLAYER/7)/ 100);
    position.case_bg.casy = (cameraRect->y + ((6/7)*DIM_SPRITE_PLAYER)) / 120;

    position.case_bd.casx = (cameraRect->x + ((6/7)*DIM_SPRITE_PLAYER)) / 100;
    position.case_bd.casy = (cameraRect->y + ((6/7)*DIM_SPRITE_PLAYER)) / 120;

    printf("case : %d , %d\n", position.case_hg.casx, position.case_hg.casy);

    afficherCarte(tab, rendu, tabTile, cameraRect, position);
}


SDL_Texture *creationTextureBar(SDL_Renderer *rendu, Couleur_t couleur){
    SDL_Surface *barSurface = SDL_CreateRGBSurface(0, HEALTH_BAR_WIDTH, HEALTH_BAR_HEIGHT, 32, 0, 0, 0, 0);
    SDL_FillRect(barSurface, NULL, SDL_MapRGB(barSurface->format, couleur.red, couleur.green, couleur.blue));
    SDL_Texture *barTexture = SDL_CreateTextureFromSurface(rendu, barSurface);
    SDL_FreeSurface(barSurface);
    return barTexture;


}

// Initialise la barre de vie du joueur au max
void initHealthBar(HealthBar *healthBar, int x, int y, int maxWidth) {
    healthBar -> x = x;
    healthBar -> y = y;
    healthBar -> width = maxWidth;
    healthBar -> maxWidth = maxWidth;
}

// Met à jour la barre de vie du joueur (currentHealth prend un pourcentage)
void updateHealthBar(HealthBar *healthBar, SDL_Rect *healthBarRect, int currentHealth) {
    healthBarRect->w = (currentHealth * healthBar->maxWidth) / 100;
}

/* Fonction d'initialisation du tableau de tiles */

int tabInit(SDL_Texture *tab[5], SDL_Renderer* rendu){
    int i = 0;
    const char* paths[] = {
        "images/tile0.png",
        "images/tile1.png",
        "images/tile2.png",
        "images/tile3.png",
        "images/tile4.png"
    };
    for (i = 0; i < 5; i++) {
        SDL_Surface* temp_surface = IMG_Load(paths[i]);
        if (!temp_surface) {
            printf("Erreur de chargement de l'image '%s': %s\n", paths[i], SDL_GetError());
            return -1;
        }
        tab[i] = SDL_CreateTextureFromSurface(rendu, temp_surface);
        SDL_FreeSurface(temp_surface);
        if (!tab[i]) {
            printf("Erreur de création de la texture pour '%s': %s\n", paths[i], SDL_GetError());
            return -1;
        }
    }
    return 0;
}
