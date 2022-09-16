/**
 * \file database.h
 * \brief Programme déclarant les constantes, structures et fonctions nécessaires à tous les modules
 * \author IOPETI Hugo
 * \author YVOZ Ludovic
 * \date 12 novembre 2020
 */

#ifndef SCREEN_WIDTH
#include "fonctions_SDL.h"
#include <time.h>
#include <stdio.h>


/**
 * \brief Largeur de l'écran de jeu
 */
#define SCREEN_WIDTH 700

/**
 * \brief Hauteur de l'écran de jeu
 */
#define SCREEN_HEIGHT 400  

/**
 * \brief Coordonnée x du mur droit de la zone de jeu 
 */
#define PLAY_ZONE_RIGHT_WALL 573

/**
 * \brief Coordonnée x du mur gauche de la zone de jeu 
 */
#define PLAY_ZONE_LEFT_WALL 125

/**
 * \brief Coordonnée y du mur en haut de la zone de jeu 
 */
#define PLAY_ZONE_TOP_WALL 84

/**
 * \brief Coordonnée y du mur en bas de la zone de jeu 
 */
#define PLAY_ZONE_BOTTOM_WALL 308

/**
 * \brief Coordonnée x de la porte en haut
 */
#define PLAY_ZONE_ADD_TOP_X 284

/**
 * \brief Coordonnée x de la porte en haut et en bas mais de l'autre côté
 */
#define PLAY_ZONE_ADD_TOP_BOT_X_2 413

/**
 * \brief Epaisseur des murs vus de haut
 */
#define WALL_WIDTH 22

/**
 * \brief Epaisseur du poteau qui tient la porte
 */
#define POST_WIDTH 11

/**
 * \brief Coordonnée y de la porte à gauche
 */
#define PLAY_ZONE_ADD_LEFT_Y 83

/**
 * \brief Coordonnée x de la porte à gauche et à droite mais de l'autre côté
 */
#define PLAY_ZONE_ADD_LEFT_RIGHT_Y_2 244

/**
 * \brief Epaisseur des murs du haut à gauche vus de côté
 */
#define WALL_WITDH_LEFT 66

/**
 * \brief Epaisseur des murs du bas à gauche vus de côté
 */
#define WALL_WITDH_LEFT_2 64

/**
 * \brief Type qui correspond à un étage du jeu sous forme de liste
 */

typedef struct Liste_s Liste_t;

/**
 * \brief Représentation d'un étage du jeu sous forme de liste chaînée
*/

struct Liste_s
{
    Liste_t* suivant;   /*!< Champ représentant l'élément suivant dans la liste */
    int direction;      /*!< Champ représentant la direction dans laquelle se trouve la chambre suivante (0 : bas, 1 : droite, 2 : gauche, 3 : haut) */
    int type;           /*!< Champ représentant le type de salle (0 : salle normale, 1 : salle de boss)*/
};


/**
 * \brief Représentation d'un sprite du jeu
*/

struct sprite_s
{
    int x;          /*!< Champ indiquant la position du centre du sprite (sur l'abscisse) */
    int y;          /*!< Champ indiquant la position du centre du sprite (sur l'ordonnée) */
    int h;          /*!< Champ indiquant la hauteur du sprite */
    int* w;         /*!< Champ indiquant la largeur du sprite (varie selon la colonne sur laquelle se trouve le sprite dans la sprite sheet) */
    int v;          /*!< Champ indiquant la vitesse du sprite */
    int is_visible; /*!< Champ indiquant si le sprite est visible (0) ou invisible (1) */
    int* wich_img;  /*!< Champ indiquant quelle image doit être affichée pour le sprite à l'instant, [0] = n° sur l'axe x et [1] = n° sur l'axe y */
};

/**
 * \brief Type qui correspond à un sprite du jeu
 */

typedef struct sprite_s sprite_t;

struct character_s
{
    sprite_t *sprite;           /*!< Champ représentant le sprite du personnage */
    sprite_t *atk_sprite_hori;  /*!< Champ représentant le sprite de l'attaque du personnage (forme horizontale) */
    sprite_t *atk_sprite_verti; /*!< Champ représentant le sprite de l'attaque du personnage (forme verticale) */
    int hp;                     /*!< Champ indiquant le nombre de points de vie du personnage */   
    int atk_power;              /*!< Champ indiquant la puissance d'attaque du personnage */
    int atk_speed;              /*!< Champ indiquant la vitesse d'attaque du personnage */
    int atk_speed_timer;        /*!< Champ indiquant le nombre de boucles nécessaires à l'attaque du joueur */
    int animation_timer;        /*!< Champ indiquant le nombre de boucles nécessaires à l'animation du joueur */
    int invincibility_timer;    /*!< Champ indiquant le nombre de boucles durant lesquelles le joueur est invincible */
    int is_invincible;          /*!< Champ indiquant si le joueur est actuellement invincible ou non (0 si oui, 1 si non)*/
    int bonus_hp;               /*!< Champ indiquant le bonus de pv du personnage (obtenu en finissant une partie) */
    int bonus_atk_power;        /*!< Champ indiquant le bonus d'attaque du personnage (obtenu en finissant une partie) */   
    int bonus_atk_speed;        /*!< Champ indiquant le bonus de vitesse d'attaque du personnage (obtenu en finissant une partie) */   
};

/**
 * \brief Type qui correspond aux données du personnage du joueur
 */

typedef struct character_s character_t;


struct missile_s
{
    sprite_t *sprite;       /*!< Champ représentant le sprite du missile */
    int atk_power;          /*!< Champ indiquant la puissance d'attaque du missile */
    int target_x;           /*!< Champ indiquant la coordonnée en abscisse de la cible du missile */
    int target_y;           /*!< Champ indiquant la coordonnée en ordonnée de la cible du missile */
    int nb_turret;          /*!< Champ indiquant la coordonnée en abscisse de la tourelle du missile */
    int timer_missile;      /*!< Champ indiquant un compteur avant la disparition du missile ce qui simule une portée maximum à la tourelle */
};

/**
 * \brief Type qui correspond aux données des missiles
 */

typedef struct missile_s missile_t;


struct monster_s
{
    sprite_t *sprite;       /*!< Champ représentant le sprite du monstre */
    int hp;                 /*!< Champ indiquant le nombre de points de vie du monstre */     
    int atk_power;          /*!< Champ indiquant la puissance d'attaque du monstre */
    int type;               /*!< Champ indiquant le type du monstre (1 = ... / 2 = ... / etc..) */
    int atk_speed;          /*!< Champ indiquant la vitesse d'attaque du monstre */
    int invincibility_timer;/*!< Champ indiquant le nombre de boucles durant lesquelles le monstre est invincible */
    int is_invincible;      /*!< Champ indiquant si le monstre est actuellement invincible ou non (0 si oui, 1 si non)*/
};

/**
 * \brief Type qui correspond aux données des monstres
 */

typedef struct monster_s monster_t;


struct boss_s
{
    sprite_t *sprite;           /*!< Champ représentant le sprite du boss */
    sprite_t *atk_sprite;       /*!< Champ représentant le sprite de l'attaque du boss */
    int hp;                     /*!< Champ indiquant le nombre de points de vie du boss */   
    int atk_power;              /*!< Champ indiquant la puissance d'attaque du boss */
    int atk_speed;              /*!< Champ indiquant la vitesse d'attaque du boss */
    int atk_speed_timer;        /*!< Champ indiquant le nombre de boucles nécessaires à l'attaque du boss */
    int animation_timer;        /*!< Champ indiquant le nombre de boucles nécessaires à l'animation du boss */
    int atk_animation_timer;    /*!< Champ indiquant le nombre de boucles nécessaires à l'animation de l'attaque du boss */
    int invincibility_timer;    /*!< Champ indiquant le nombre de boucles durant lesquelles le boss est invincible */
    int is_invincible;          /*!< Champ indiquant si le boss est actuellement invincible ou non (0 si oui, 1 si non)*/
};

/**
 * \brief Type qui correspond aux données du boss
 */

typedef struct boss_s boss_t;


/**
 * \brief Représentation du monde du jeu
*/

struct world_s
{
    character_t *player;    /*!< Champ représentant le personnage du joueur */
    boss_t* boss;           /*!< Champ représentant le boss */
    int play_again;         /*!< Champ indiquant si le joueur souhaite rejouer (1 si oui, 0 si non, 2 si on ne sait pas encore) */
    int gameover;           /*!< Champ indiquant si l'on est à la fin du jeu (1 si oui, 0 si non) */
    missile_t** missiles;   /*!< Champ représentant les missiles des monstre tourelle */
    int nb_missiles;        /*!< Champ représentant le nombre de missiles en jeu */
    monster_t **enemies;    /*!< Champ représentant les ennemis en jeu */
    int nb_enemies;         /*!< Champ représentant le nombre d'ennemis en jeu */
    int nb_enemies_max;     /*!< Champ représentant le nombre d'ennemis maximum pour la salle actuelle */
    int nb_enemies_min;     /*!< Champ représentant le nombre d'ennemis minimum pour la salle actuelle */
    int score;              /*!< Champ représentant le score du joueur */
    int game_state;         /*!< Champ représentant l'état de la partie en cours (1 = J perdu / 2 = E tous détruits / 3 = partie pas finie) */
    int room_state;         /*!< Champ représentant l'état de la salle actuelle (0 = entrée dans la salle / 1 = bataille en cours /2 = E tous détruits / etc... boos, shop,...) */             
    Liste_t* floor;         /*!< Champ représentant un étage du jeu sous forme de liste chaînée */
    int wants_reward;       /*!< Champ représentant le fait que le joueur ait demandé sa récompense (utile pour l'affichage) (0 si oui, 1 si non) */
    int is_paused;          /*!< Champ représentant le  fait que le jeu soit mis en pause (0 si oui, 1 si non) */
};

/**
 * \brief Type qui correspond aux données du monde
 */

typedef struct world_s world_t;

/**
 * \brief La procédure initialise les données d'un sprite
 * \param sprite le sprite à initialiser
 * \param x la position du centre du sprite (sur l'abscisse)
 * \param y la position du centre du sprite (sur l'ordonnée)
 * \param h la hauteur du sprite
 * \param w tableau contenant les largeurs des sprites selon leur position sur la sprite cheet
 * \param v la vitesse du sprite
 */
void init_sprite(sprite_t *sprite, int x, int y, int* w, int h, int v);

/**
 * \brief Fonction qui génère un nombre aléatoire.
 * \param a Borne inférieure.
 * \param b Borne supérieure.
 * \return Un nombre compris entre \a a (inclus) et \a b (non-inclus).
 */
int generate_number(int a, int b);

/**
 * \brief La procédure rends le sprite visible
 * \param sprite le sprite à modifier
 */
void set_visible(sprite_t *sprite);

/**
 * \brief La procédure rends le sprite invisible
 * \param sprite le sprite à modifier
 */
void set_invisible(sprite_t *sprite);

/**
 * \brief La fonction indique si le jeu est fini en fonction des données du monde
 * \param world les données du monde
 * \return 1 si le jeu est fini, 0 sinon
 */
int is_game_over(world_t *world);


/**
 * \brief La fonction regarde si le sprite donné est en dehors de la zone de jeu
 * \param sprite Un sprite
 * \return Retourne 0 si vrai et 1 si faux
 */
int sprite_is_out_of_bounds(sprite_t* sprite);


/**
 * \brief La fonction regarde si le sprite donné est en dehors des zones de jeu additionelles si la salle est finie
 * \param sprite Un sprite
 * \param direction La direction dans laquelle se trouve la prochaine salle
 * \param room_state L'état de la salle
 * \return Retourne 0 si vrai et 1 si faux
 */
int sprite_is_out_of_additional_bounds(sprite_t* sprite, int direction, int room_state);


/**
 * \brief La fonction change l'image affichée du sprite
 * \param sprite Un sprite
 * \param x Le n° de l'image sur l'axe des abscisses dans son sprite sheet
 * \param y Le n° de l'image sur l'axe des abscisses dans son sprite sheet
 */
void set_img_sprite(sprite_t* sprite, int x, int y);


#endif
