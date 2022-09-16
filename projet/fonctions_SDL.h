/**
 * \file fonctions_SDL.h
 * \brief Programme déclarant la fonction fonctions_SDL.h
 * \author IOPETI Hugo
 * \author YVOZ Ludovic
 * \date 21 septembre 2020
 */

#ifndef load_image
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>



/**
 * \brief Fonction qui charge une image et retourne la surface de texture
 * \param nomfichier Nom du fichier
 * \param renderer Le renderer
 * \return La surface de la texture chargée
 */
SDL_Texture *load_image(const char *nomfichier, SDL_Renderer *renderer);


/**
 * \brief Fonction qui charge une image transparente
 * \param nomfichier Nom du fichier
 * \param renderer Le renderer
 * \param renderer r codage rgb de R pour la couleur transparente
 * \param renderer g codage rgb de G pour la couleur transparente
 * \param renderer b codage rgb de B pour la couleur transparente
 * \return La surface de la texture chargée
 */
SDL_Texture *load_transparent_image(const char *nomfichier, SDL_Renderer *renderer, Uint8 r, Uint8 g, Uint8 b);


/**
 * \brief Fonction qui charge le texte
 * \param message Le message à charger
 * \param renderer Le renderer
 * \param font La police du texte
 * \param color La couleur du texte
 * \return La surface de la texture chargée
 */
SDL_Texture *load_text(const char *message, SDL_Renderer *renderer, TTF_Font *font, SDL_Color color);


/**
 * \brief Fonction qui nettoie une image en mémoire
 * \param image L'image à nettoyer
 */
void clean_image(SDL_Texture* image);


/**
 * \brief Fonction qui applique une image sur le renderer à une certaine position
 * \param image L'image à afficher
 * \param renderer Le renderer
 * \param SrcR Stockage de la position et des dimensions du sprite à afficher
 * \param x Position de l'image à afficher sur l'abscisse de la fenêtre
 * \param y Position de l'image à afficher sur l'ordonnée de la fenêtre
 */
void apply_image(SDL_Texture* image, SDL_Renderer* renderer, SDL_Rect SrcR, int x, int y);

/**
 * \brief Fonction qui initialise la fenêtre graphique et le renderer
 * \param window la fenêtre du jeu
 * \param renderer le renderer
 * \param width largeur de l'écran de jeu
 * \param height hauteur de l'écran de jeu
 */
void init_sdl(SDL_Window **window, SDL_Renderer **renderer, int width, int height);

/**
 * \brief Fonction qui nettoie tout ce qui à été initialisé dans la fonction init_SDL et ferme la fenêtre graphique
 * \param renderer Le renderer
 * \param window La fenêtre graphique
 */
void clean_sdl(SDL_Renderer *renderer,SDL_Window *window);

/**
 * \brief La fonction charge une police
 * \param path le chemin du fichier correpondant à la police
 * \param font_size la taille de la police
 * \return la police chargée
*/
TTF_Font * load_font(const char *path, int font_size);

/**
 * \brief La fonction nettoie une police
 * \param font La police à nettoyer
 */
void clean_font(TTF_Font * font);

/**
 * \brief Fonction qui initialise l'environnement ttf
 */
void init_ttf();
#endif