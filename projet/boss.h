/**
 * \file boss.h
 * \brief Programme déclarant les fonctions relatives au boss
 * \author IOPETI Hugo
 * \author YVOZ Ludovic
 * \date 3 Janvier 2021
 */

#ifndef init_boss
#include "database.h"

/**
 * \brief Hauteur du boss
 */

#define BOSS_HEIGHT 35

/**
 * \brief Largeur du boss pour les sprites de la colonne 1 et 6 du sprite sheet
 */

#define BOSS_SPRITE_COLUMN_1_6_WIDTH 82

/**
 * \brief Largeur du boss pour les sprites de la colonne 2 et 5 du sprite sheet
 */

#define BOSS_SPRITE_COLUMN_2_5_WIDTH 78

/**
 * \brief Largeur du boss pour les sprites de la colonne 3 et 4 du sprite sheet
 */

#define BOSS_SPRITE_COLUMN_3_4_WIDTH 79


/**
 * \brief Vitesse du boss
*/

#define BOSS_SPEED 8

/**
 * \brief Points de vie du boss
*/

#define BOSS_HP 500

/**
 * \brief Dégats du boss
*/

#define BOSS_ATK_POWER 15

/**
 * \brief Vitesse d'attaque du boss
*/

#define BOSS_ATK_SPEED 1

/**
 * \brief Nombres de colonnes de sprites sur la sprite cheet du boss
*/

#define NB_COLUMN_SPRITE_SHEET_BOSS 6

/**
 * \brief Nombres de colonnes de sprites sur la sprite cheet de l'attaque du boss
*/

#define NB_COLUMN_SPRITE_SHEET_BOSS_ATTACK 16

/**
 * \brief Hauteur de l'attaque du boss
 */

#define BOSS_ATTACK_HEIGHT 30

/**
 * \brief Largeur de l'attaque du boss pour les sprites de la colonne 1, 2, 15 et 16 du sprite sheet
 */

#define BOSS_ATTACK_SPRITE_COLUMN_1_2_15_16_WIDTH 34

/**
 * \brief Largeur de l'attaque du boss pour les sprites de la colonne 3 et 14 du sprite sheet
 */

#define BOSS_ATTACK_SPRITE_COLUMN_3_14_WIDTH 35

/**
 * \brief Largeur de l'attaque du boss pour les sprites de la colonne 4, 6, 11 et 13 du sprite sheet
 */

#define BOSS_ATTACK_SPRITE_COLUMN_4_6_11_13_WIDTH 19

/**
 * \brief Largeur de l'attaque du boss pour les sprites de la colonne 5 et 12 du sprite sheet
 */

#define BOSS_ATTACK_SPRITE_COLUMN_5_12_WIDTH 17

/**
 * \brief Largeur de l'attaque du boss pour les sprites de la colonne 7 et 10 du sprite sheet
 */

#define BOSS_ATTACK_SPRITE_COLUMN_7_10_WIDTH 18

/**
 * \brief Largeur de l'attaque du boss pour les sprites de la colonne 8 et 9 du sprite sheet
 */

#define BOSS_ATTACK_SPRITE_COLUMN_8_9_WIDTH 16

/**
 * \brief La distance horizontale à laquelle le boss commence à attaquer le joueur
 */
#define ATK_DISTANCE_X 76

/**
 * \brief La distance verticale à laquelle le boss commence à attaquer le joueur
 */
#define ATK_DISTANCE_Y 20

/**
 * \brief La procédure initialise le boss
 * \param world Les données du monde
 */
void init_boss(world_t* world);

/**
 * \brief La procédure crée le boss dans la salle
 * \param world Les données du monde
 */
void create_boss(world_t* world);

/**
 * \brief Procédure qui mets à jour les données du boss.
 * \param world Données du monde.
 */
void update_boss(world_t* world);

/**
 * \brief La procédure gère l'animation du boss
 * \param world Les données du monde
 */
void handle_anim_boss(world_t * world);

/**
 * \brief La procédure gère l'animation de l'attaque du boss
 * \param world Les données du monde
 */
void handle_anim_boss_atk(world_t * world);

/**
 * \brief La procédure gère la vitesse d'attaque du boss
 * \param world Les données du monde
 */
void handle_atk_speed_boss (world_t* world);

/**
 * \brief La procédure nettoie le boss
 * \param world Les données du monde
 */
void free_boss(world_t* world);

#endif