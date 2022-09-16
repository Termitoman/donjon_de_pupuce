/**
 * \file player.h
 * \brief Programme déclarant les fonctions relatives au personnage du joueur
 * \author IOPETI Hugo
 * \author YVOZ Ludovic
 * \date 24 novembre 2020
 */

#ifndef init_player
#include "database.h"
#include "fonctions_fichiers.h"


/**
 * \brief Hauteur du personnage
 */

#define PLAYER_HEIGHT 38

/**
 * \brief Largeur du personnage pour les sprites de la colonne 1 du sprite sheet
 */

#define PLAYER_SPRITE_COLUMN_1_WIDTH 31

/**
 * \brief Largeur du personnage pour les sprites de la colonne 2 du sprite sheet
 */

#define PLAYER_SPRITE_COLUMN_2_WIDTH 41

/**
 * \brief Largeur du personnage pour les sprites de la colonne 3 du sprite sheet
 */

#define PLAYER_SPRITE_COLUMN_3_WIDTH 25

/**
 * \brief Largeur du personnage pour les sprites de la colonne 4 du sprite sheet
 */

#define PLAYER_SPRITE_COLUMN_4_WIDTH 40

/**
 * \brief Largeur du personnage pour les sprites de la colonne 5 du sprite sheet
 */

#define PLAYER_SPRITE_COLUMN_5_WIDTH 27

/**
 * \brief Largeur du personnage pour les sprites de la colonne 6 du sprite sheet
 */

#define PLAYER_SPRITE_COLUMN_6_WIDTH 36

/**
 * \brief Largeur du personnage pour les sprites de la colonne 7 du sprite sheet
 */

#define PLAYER_SPRITE_COLUMN_7_WIDTH 32

/**
 * \brief Largeur du personnage pour les sprites de la colonne 8 du sprite sheet
 */

#define PLAYER_SPRITE_COLUMN_8_WIDTH 37

/**
 * \brief Nombres de colonnes de sprites sur la sprite cheet du personnage
*/

#define NB_COLUMN_SPRITE_SHEET_PLAYER 8

/**
 * \brief Nombres de colonnes de sprites sur la sprite cheet de l'attaque du personnage
*/

#define NB_COLUMN_SPRITE_SHEET_PLAYER_ATTACK 2

/**
 * \brief Largeur de l'attaque du personnage
 */

#define PLAYER_ATTACK_HORI_WIDTH 38

/**
 * \brief Hauteur de l'attaque du personnage
 */

#define PLAYER_ATTACK_HORI_HEIGHT 9

/**
 * \brief Largeur de l'attaque du personnage
 */

#define PLAYER_ATTACK_VERTI_WIDTH 9

/**
 * \brief Hauteur de l'attaque du personnage
 */

#define PLAYER_ATTACK_VERTI_HEIGHT 38

/**
 * \brief Vitesse du personnage
*/

#define PLAYER_SPEED 28

/**
 * \brief Points de vie du personnage
*/

#define PLAYER_HP 100

/**
 * \brief Dégats du personnage
*/

#define PLAYER_ATK_POWER 50

/**
 * \brief Vitesse d'attaque du personnage
*/

#define PLAYER_ATK_SPEED 3

/**
 * \brief La procédure initialise le personnage du joueur
 * \param world Les données du monde
 */
void init_player(world_t* world);

/**
 * \brief La procédure gère l'animation du personnage
 * \param world Les données du monde
 */
void handle_anim_player(world_t * world);

/**
 * \brief La procédure gère la vitesse d'attaque du personnage
 * \param world Les données du monde
 */
void handle_atk_speed_player (world_t* world);

/**
 * \brief La procédure nettoie le personnage du joueur
 * \param world Les données du monde
 */
void free_player(world_t* world);

#endif
