/**
 * \file map.c
 * \brief Programme définissant les fonctions déclarées dans map.h
 * \author YVOZ Ludovic
 * \author IOPETI Hugo
 * \date 29 Décembre 2020
 */

#include "map.h"


void init_floor(world_t* world) {
    //On crée la carte
    world->floor = malloc(sizeof(Liste_t));
    world->floor->type = 0;
    world->floor->direction = generate_number(0, 4);

    int nb_rooms = generate_number(NB_SALLES_MIN, NB_SALLES_MAX);

    create_rooms(world->floor, nb_rooms);
}

void create_rooms(Liste_t* liste, int nb_rooms) {
    if (nb_rooms > 0) {
        liste->suivant = malloc(sizeof(*liste->suivant));
        liste->suivant->type = 0;
        liste->suivant->direction = generate_number(0, 4);
        create_rooms(liste->suivant, nb_rooms-1);
    }
    else if (nb_rooms == 0) {
        liste->suivant = malloc(sizeof(*liste->suivant));
        liste->suivant->type = 1;
        liste->suivant->direction = generate_number(0, 4);
        liste->suivant->suivant = NULL;
    }
}

void free_floor(Liste_t* liste) {
    if (liste->suivant != NULL) {
        free_floor(liste->suivant);
    }
    else {
        free(liste);
    }
}