/**
 * \file init_and_clean.h
 * \brief Programme déclarant les fonctions qui initialisent et nettoient les données
 * \author YVOZ Ludovic
 * \author IOPETI Hugo
 * \date 23 Novembre 2020
 */
 
#ifndef init_data
#include "database.h"
#include "player.h"
#include "enemy.h"
#include "map.h"
#include "boss.h"


/**
 * \brief La fonction initialise les données du monde du jeu
 * \param world les données du monde
 */
void init_data(world_t * world);


/**
 * \brief La fonction nettoie les données du monde
 * \param world les données du monde
 */
void clean_data(world_t *world);

/**
 * \brief Procédure qui initialise les ennemis.
 * \param world Données du monde.
 */
void init_enemies(world_t* world);

#endif