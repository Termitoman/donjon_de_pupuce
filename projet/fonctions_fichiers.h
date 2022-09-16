/**
 * \file fonctions_fichiers.h
 * \brief Programme déclarant des fonctions effectuant une lecture ou écriture de fichiers
 * \author IOPETI Hugo
 * \author YVOZ Ludovic
 * \date 31 Décembre 2020
 */

#ifndef init_file
#include <stdlib.h>
#include "database.h"

/**
 * \brief Fonction qui ouvre le fichier de sauvegarde et redonne les bonus écrits dedans si le fichier existe, sinon les bonus sont mis à 0.
 * \param world Les données du monde.
 */
void read_saved_file(world_t* world);

/**
 * \brief Fonction qui ouvre le fichier de sauvegarde, efface ce qu'il y a dedans et écrit les bonus actuels, si il n'y a pas de fichier, on en créer un.
 * \param world Les données du monde.
 */
void write_saved_file(world_t* world);

#endif
