/**
 * \file enemy.h
 * \brief Programme déclarant les fonctions relatives aux monstres
 * \author IOPETI Hugo
 * \author YVOZ Ludovic
 * \date 24 novembre 2020
 */

#ifndef init_enemies
#include "database.h"


/**
 * \brief Hauteur des ennemis de type 1
 */

#define ENEMY_1_HEIGHT 24

/**
 * \brief Largeur des ennemis de type 1
 */

#define ENEMY_1_WIDTH 42

/**
 * \brief Vitesse des ennemis de type 1
*/

#define ENEMY_1_SPEED 1

/**
 * \brief Points de vie des ennemis de type 1
*/

#define ENEMY_1_HP 100

/**
 * \brief Dégats des ennemis de type 1
*/

#define ENEMY_1_ATK_POWER 5

/**
 * \brief Vitesse d'attaque des ennemis de type 1
*/

#define ENEMY_1_ATK_SPEED 101

/**
 * \brief Hauteur des ennemis de type 2
 */

#define ENEMY_2_HEIGHT 35

/**
 * \brief Largeur des ennemis de type 2
 */

#define ENEMY_2_WIDTH 25

/**
 * \brief Vitesse des ennemis de type 2
*/

#define ENEMY_2_SPEED 3

/**
 * \brief Dégats des ennemis de type 2
*/

#define ENEMY_2_ATK_POWER 20

/**
 * \brief Vitesse d'attaque des ennemis de type 2
*/

#define ENEMY_2_ATK_SPEED 51

/**
 * \brief Points de vie des ennemis de type 2
*/

#define ENEMY_2_HP 55

/**
 * \brief Hauteur des ennemis de type 3
 */

#define ENEMY_3_HEIGHT 22

/**
 * \brief Largeur des ennemis de type 3 
 */

#define ENEMY_3_WIDTH 29

/**
 * \brief Vitesse des ennemis de type 3
*/

#define ENEMY_3_SPEED 0

/**
 * \brief Dégats des ennemis de type 3
*/

#define ENEMY_3_ATK_POWER 1

/**
 * \brief Vitesse d'attaque des ennemis de type 3
*/

#define ENEMY_3_ATK_SPEED 145

/**
 * \brief Points de vie des ennemis de type 3
*/

#define ENEMY_3_HP 180

/**
 * \brief Hauteur des missiles
 */

#define MISSILE_HEIGHT 16

/**
 * \brief Largeur des missiles
 */

#define MISSILE_WIDTH 17

/**
 * \brief Vitesse des missiles
*/

#define MISSILE_SPEED 1

/**
 * \brief Dégats des missiles
*/

#define MISSILE_ATK_POWER 25

/**
 * \brief Nombre d'ennemis maximum pour la première salle
*/

#define NB_ENEMIES_MAX 10

/**
 * \brief La distance entre l'apparition des monstres et le joueur au début d'une salle
*/

#define SPAWN_DISTANCE 50

/**
 * \brief La procédure initialise les ennemis
 * \param world Les données du monde
 */
void init_enemies(world_t* world);

/**
 * \brief La procédure initialise les missiles
 * \param world Les données du monde
 */
void init_missiles(world_t* world);

/**
 * \brief La procédure crée les ennemis d'une salle
 * \param world Les données du monde
 */
void create_enemies(world_t* world);

/**
 * \brief La procédure crée les missiles d'une salle
 * \param world Les données du monde
 */
void create_missiles(world_t* world);

/**
 * \brief La procédure nettoie les ennemis
 * \param world Les données du monde
 */
void free_enemies(world_t* world);

/**
 * \brief La procédure nettoie les missiles
 * \param world Les données du monde
 */
void free_missiles(world_t* world);

/**
 * \brief Procédure qui mets à jour les données des ennemis.
 * \param world Données du monde.
 */
void update_enemies(world_t* world);

/**
 * \brief Procédure qui mets à jour les données des missiles.
 * \param world Données du monde.
 */
void update_missiles(world_t* world);

/**
 * \brief Procédure qui gère le timer des missiles
 * \param world Données du monde.
 */
void handle_missile_timer(world_t* world);

#endif
