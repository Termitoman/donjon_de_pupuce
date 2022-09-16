/**
 * \file graphique.h
 * \brief Programme déclarant les fonctions graphiques
 * \author IOPETI Hugo
 * \author YVOZ Ludovic
 * \date 30 avril 2020
 */
 
#ifndef apply_sprite
#include "database.h"

/**
 * \brief Ecart entre les lignes d'une sprite sheet
 */
#define SPACE_BETWEEN_ROWS 26

/**
 * \brief Ecart entre les colonnes d'une sprite sheet
 */
#define SPACE_BETWEEN_COLUMNS 5


/**
 * \brief Représentation pour stocker les ressources nécessaires à l'affichage graphique des salles
*/

struct room_resources_s{
    SDL_Texture* background;            /*!< Texture liée à l'image du fond de l'écran */
    SDL_Texture* door_down_close;       /*!< Texture liée à l'image de la porte du bas fermée */
    SDL_Texture* door_up_close;         /*!< Texture liée à l'image de la porte du haut fermée */
    SDL_Texture* door_down_open;        /*!< Texture liée à l'image de la porte du bas fermée */
    SDL_Texture* door_up_open;          /*!< Texture liée à l'image de la porte du haut fermée */
    SDL_Texture* door_right_close;      /*!< Texture liée à l'image de la porte de droite fermée */ 
    SDL_Texture* door_right_open;       /*!< Texture liée à l'image de la porte de droite ouvert */  
    SDL_Texture* door_left_close;       /*!< Texture liée à l'image de la porte de gauche fermée */
    SDL_Texture* door_left_open;        /*!< Texture liée à l'image de la porte de gauche ouverte */
    SDL_Texture* wall_down;             /*!< Texture liée à l'image du mur du bas */
    SDL_Texture* wall_up;               /*!< Texture liée à l'image du mur du haut */
    SDL_Texture* wall_right;            /*!< Texture liée à l'image du mur de droite */ 
    SDL_Texture* wall_left;             /*!< Texture liée à l'image du mur de gauche */
};

/**
 * \brief Type qui correspond aux ressources des salles
*/

typedef struct room_resources_s room_resources_t;


/**
 * \brief Représentation pour stocker les ressources nécessaires à l'affichage des images additionnelles
*/

struct add_disp_s{
    SDL_Texture* pause_screen;          /*!< Texture liée à l'image diffusée lorsque le jeu est en pause */
    SDL_Texture* black_background;      /*!< Texture liée à l'image d'un fond entièrement noir */
    SDL_Texture* death_screen;          /*!< Texture liée à l'image diffusée lorsque le joueur meurt */
    SDL_Texture* rules;                 /*!< Texture liée à l'image diffusée avant que la partie commence pour lui expliquer les règles */
    SDL_Texture* end_screen;            /*!< Texture liée à l'image diffusée lorsque le joueur quitte le jeu */
    SDL_Texture* welcome_screen;        /*!< Texture liée à l'image diffusée lorsque le joueur commence le jeu */
    SDL_Texture* waiting_screen_1;      /*!< Texture liée à l'image diffusée lorsque le compte à rebours avant que le jeu démarre en est à 1 */
    SDL_Texture* waiting_screen_2;      /*!< Texture liée à l'image diffusée lorsque le compte à rebours avant que le jeu démarre en est à 2 */
    SDL_Texture* waiting_screen_3;      /*!< Texture liée à l'image diffusée lorsque le compte à rebours avant que le jeu démarre en est à 3 */
};

/**
 * \brief Type qui correspond aux ressources additionnelles du jeu
*/

typedef struct add_disp_s add_disp_t;


/**
 * \brief Représentation pour stocker les ressources nécessaires à l'affichage graphique
*/

struct resources_s{
    room_resources_t* room;             /*!< Textures liées à l'image de la salle */
    add_disp_t* add_disp;               /*!< Textures liées aux images additionelles à afficher */
    SDL_Texture* player;                /*!< Texture liée à l'image du personnage. */
    SDL_Texture* player_attack_hori;    /*!< Texture liée à l'image de l'attaque du personnage (forme horizontale) */
    SDL_Texture* player_attack_verti;   /*!< Texture liée à l'image de l'attaque du personnage (forme verticale)*/   
    SDL_Texture* slime;                 /*!< Texture liée à l'image des slimes. */
    SDL_Texture* vertical_skull;        /*!< Texture liée à l'image des crânes qui trversent la salle verticalement */
    SDL_Texture* skull_turret;          /*!< Texture liée à l'image de la tourelle. */
    SDL_Texture* skull_projectile;      /*!< Texture liée à l'image des projectiles de la tourelle. */
    SDL_Texture* boss;                  /*!< Texture liée à l'image du boss */
    SDL_Texture* boss_atk;              /*!< Texture liée à l'image de l'attaque du boss */
    TTF_Font* font;                     /*!< Police de caractères utilisées pour les textes à afficher sur la fenêtre */
    TTF_Font* smaller_font;             /*!< Police de caractères utilisées pour les textes à afficher sur la fenêtre mais en plus petit */
    SDL_Color color;                    /*!< Couleur de la police d'écriture */
};

/**
 * \brief Type qui correspond aux ressources du jeu
*/

typedef struct resources_s resources_t;



/**
 * \brief La procédure applique une texture sur le renderer à sa position
 * \param renderer Le renderer actuel
 * \param texture La texture à appliquer
 * \param sprite Le sprite dont on doit appliquer la texture
*/
void apply_sprite(SDL_Renderer * renderer, SDL_Texture * texture, sprite_t * sprite);


/**
 * \brief La fonction initialise les texures
 * \param screen la surface correspondant à l'écran de jeu
 * \param resources les ressources du jeu
*/
void  init_resources(SDL_Renderer *renderer, resources_t *resources);


/**
 * \brief La fonction nettoie les ressources
 * \param resources les ressources
*/
void clean_resources(resources_t *resources);


/**
 * \brief La fonction applique la texture du fond sur le renderer lié à l'écran de jeu
 * \param renderer le renderer
 * \param resources les ressources du jeu
*/
void apply_background(SDL_Renderer *renderer, resources_t *resources);


/**
 * \brief La procédure applique une texture sur le renderer à une position donnée en paramètres
 * \param renderer Le renderer actuel
 * \param texture La texture à appliquer
 * \param x la coordonnée en abscisse de l'endroit où on compte afficher la texture
 * \param y la coordonnée en ordonnée de l'endroit où on compte afficher la texture
*/
void apply_part_of_background(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y);


/**
 * \brief La fonction rafraichit l'écran en fonction de l'état des données du monde
 * \param renderer la surface de l'écran de jeu
 * \param world les données du monde
 * \param resources les ressources
 */
void refresh_graphics(SDL_Renderer *renderer, world_t *world,resources_t *resources);


/**
 * \brief La fonction s'occupe de l'affichage des portes et murs sur les côtés
 * \param renderer la surface de l'écran de jeu
 * \param world les données du monde
 * \param resources les ressources
 */
void refresh_room(SDL_Renderer *renderer, world_t *world, resources_t *resources);


/**
 * \brief La fonction applique les monstres sur le renderer
 * \param renderer la surface de l'écran de jeu
 * \param world les données du monde
 * \param resources les ressources
 */
void apply_monsters(SDL_Renderer* renderer, world_t* world, resources_t* resources);

/**
 * \brief La fonction applique les missiles sur le renderer
 * \param renderer la surface de l'écran de jeu
 * \param world les données du monde
 * \param resources les ressources
 */
void apply_missiles(SDL_Renderer* renderer, world_t* world, resources_t* resources);

/**
 * \brief La procédure applique un texte sur le renderer
 * \param renderer Le renderer actuel
 * \param font La police d'écriture à appliquer
 * \param color La couleur du texte à appliquer
 * \param strin Le texte à appliquer
 * \param x la coordonnée en abscisse de l'endroit où on compte afficher le texte
 * \param y la coordonnée en ordonnée de l'endroit où on compte afficher le texte
*/
void apply_text(SDL_Renderer * renderer, TTF_Font* font, SDL_Color color, char * string, int x, int y);

/**
 * \brief La fonction affiche le menu des récompenses
 * \param renderer la surface de l'écran de jeu
 * \param world les données du monde
 * \param resources les ressources
 */
void reward_message(world_t* world, SDL_Renderer * renderer, resources_t* resources);

/**
 * \brief La fonction affiche un message de fin du jeu selon la situations
 * \param world les données du monde
 * \param renderer la surface de l'écran de jeu
 * \param resources les ressources
 * \param event paramètre qui contient les événements
 */
void end_screen(world_t* world, SDL_Renderer * renderer, resources_t* resources);

/**
 * \brief La fonction affiche un message lorsque le jeu est en pause
 * \param world les données du monde
 * \param renderer la surface de l'écran de jeu
 * \param resources les ressources
 */
void pause_screen(world_t* world, SDL_Renderer * renderer, resources_t* resources);


/**
 * \brief La fonction affiche les messages de début du jeu
 * \param renderer la surface de l'écran de jeu
 * \param resources les ressources
 */
void start_screen(SDL_Renderer * renderer, resources_t* resources);

#endif