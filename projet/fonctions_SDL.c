/**
 * \file fonctions_SDL.c
 * \brief Programme déclarant la fonction charger_image
 * \author IOPETI Hugo
 * \author YVOZ Ludovic
 * \date 21 septembre 2020
 */

#include "fonctions_SDL.h"

SDL_Texture *load_image(const char *file_name, SDL_Renderer *renderer){
    SDL_Surface *image = SDL_LoadBMP(file_name);
    return SDL_CreateTextureFromSurface(renderer, image);
}

SDL_Texture *load_transparent_image(const char *file_name, SDL_Renderer *renderer, Uint8 r, Uint8 g, Uint8 b){
    SDL_Surface *image_tr = SDL_LoadBMP(file_name);
    Uint32 color = SDL_MapRGB(image_tr->format, r, g, b);
    SDL_SetColorKey(image_tr, SDL_TRUE, color);
    return SDL_CreateTextureFromSurface(renderer, image_tr);
}

SDL_Texture *load_text(const char *message, SDL_Renderer *renderer, TTF_Font *font, SDL_Color color){
    SDL_Surface *image_txt = TTF_RenderText_Solid(font, message, color);
    return SDL_CreateTextureFromSurface(renderer, image_txt);
}

void clean_image(SDL_Texture* image) {
    if (image != NULL) {
        SDL_DestroyTexture(image);
    }
}

void apply_image(SDL_Texture* image, SDL_Renderer* renderer, SDL_Rect SrcR, int x, int y) {
    SDL_Rect DestR = SrcR;

    DestR.x = x; //On choisit les coordonnées de l'endroit où on affiche le sprite sur la fenêtre
    DestR.y = y;
    DestR.h = SrcR.h;
    DestR.w = SrcR.w;

    SDL_RenderCopy(renderer, image, &SrcR, &DestR); //Affichage du sprite
}

void init_sdl(SDL_Window **window, SDL_Renderer **renderer, int width, int height) {
    SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO);
    SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_SHOWN, window, renderer);
}

void clean_sdl(SDL_Renderer *renderer,SDL_Window *window){
    if(renderer != NULL) {
        SDL_DestroyRenderer(renderer);
    }
    if(window != NULL) {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();    
}

TTF_Font * load_font(const char *path, int font_size){
    TTF_Font *font = TTF_OpenFont(path, font_size);
    if(font == NULL){
        fprintf(stderr, "Erreur pendant chargement font: %s\n", SDL_GetError());
    }
    return font;
}

void clean_font(TTF_Font * font){
    TTF_CloseFont(font);
}

void init_ttf(){
    if(TTF_Init()==-1) {
        printf("TTF_Init: %s\n", TTF_GetError());
    }
}