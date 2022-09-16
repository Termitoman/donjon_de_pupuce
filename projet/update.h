/**
 * \file update.h
 * \brief Programme déclarant les fonctions utilisées pour mettre à jour les données à chaque boucle de jeu
 * \author IOPETI Hugo
 * \author YVOZ Ludovic
 * \date 24 Novembre 2020
 */
  
#ifndef update_data
#include "database.h"
#include "enemy.h"
#include "boss.h"
#include <math.h>


/**
 * \brief La fonction met à jour les données en tenant compte de la physique du monde
 * \param world données du monde
 */
void update_data(world_t *world);


/**
 * \brief Fonction qui vérifie si deux sprites sont en collision.
 * \param sp1 sprite n°1
 * \param sp2 sprite n°2
 * \return 1 en cas de collision et 0 en cas de non-collision
 */
int sprites_collide(sprite_t *sp2, sprite_t *sp1);


/**
 * \brief Procédure qui gère les attaques du personnage et des monstres
 * \param world Les données du monde
 */
void handle_attacks(world_t* world);


/**
 * \brief Procédure qui gère les attaques du personnage et du boss
 * \param world Les données du monde
 */
void handle_boss_attacks(world_t* world);


/**
 * \brief Procédure qui gère l'invincibilité du personnage et des monstres
 * \param world Les données du monde
 */
void handle_invincibility(world_t* world);


/**
 * \brief Procédure qui gère l'invincibilité du personnage et du boss
 * \param world Les données du monde
 */
void handle_boss_invincibility(world_t* world);


/**
 * \brief Procédure qui print les données d'un sprite
 * \param sprite Le sprite dont on veut afficher les données
 */
void print_sprite(sprite_t * sprite);


/**
 * \brief Procédure qui retourne le nombre d'ennemis en vie
 * \param world Données du monde.
 * \return Le nombre d'ennemis en vie.
 */
int nb_enemies_alive(world_t* world);


#endif