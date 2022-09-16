/**
 * \file map.h
 * \brief Programme déclarant les fonctions qui initialisent et gèrent les cartes des étages
 * \author YVOZ Ludovic
 * \author IOPETI Hugo
 * \date 29 Décembre 2020
 */

#ifndef create_map
#include "database.h"


/**
 * \brief Nombre de salles minimales dans un étage
*/

#define NB_SALLES_MIN 2


/**
 * \brief Nombre de salles maximales dans un étage
*/

#define NB_SALLES_MAX 4


/**
 * \brief Fonction qui génère un étage du jeu sous forme de liste chaînée.
 * \param world Les données du monde.
 */
void init_floor(world_t* world);

/**
 * \brief Fonction qui génère les salles de l'étage et qui les place dans des membres d'une liste que l'on crée au préalable.
 * \param liste Le membre de départ de la liste contenant les salles.
 * \param nb_rooms Le nombre de salles désirées.
 */
void create_rooms(Liste_t* liste, int nb_rooms);

/**
 * \brief Fonction qui nettoie une liste chaînée.
 * \param liste La liste à nettoyer.
 */
void free_floor(Liste_t* liste);

#endif