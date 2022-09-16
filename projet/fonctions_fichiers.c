/**
 * \file fonctions_fichiers.c
 * \brief Programme définissant les fonctions déclarées dans fonctions_fichiers.h
 * \author IOPETI Hugo
 * \author YVOZ Ludovic
 * \date 31 Décembre 2020
 */

#include "fonctions_fichiers.h"


void read_saved_file(world_t* world) {
    FILE* pfile = fopen("sauvegarde/sauvegarde.txt", "r");
    if (pfile == NULL) {    //Si il n'y a pas de fichier où que l'on arrive pas à ouvrir le fichier, il n'y a pas de sauvegarde, donc le joueur n'a pas de bonus
        //On affiche un message pour indiquer que le fichier s'est mal ouvert
        printf("Le fichier de sauvegarde ne s'est pas bien ouvert où n'existait pas, un nouveau fichier vierge sera crée à la fin de la partie !\n");
        world->player->bonus_hp = 0;
        world->player->bonus_atk_power = 0;
        world->player->bonus_atk_speed = 0;
    }
    else
    {   
        int temp;
        temp = fscanf(pfile, "bonus_hp : %d\n", &(world->player->bonus_hp));
        temp = fscanf(pfile, "bonus_atk_power : %d\n", &(world->player->bonus_atk_power));
        temp = fscanf(pfile, "bonus_atk_speed : %d", &(world->player->bonus_atk_speed));
        fclose(pfile);
    }
}

void write_saved_file(world_t* world) {
    FILE* pfile = fopen("sauvegarde/sauvegarde.txt", "w");
    if (pfile == NULL) {    //erreur lors de l'ouverture du fichier
        perror("Erreur lors de l'ouverture du fichier de sauvegarde");
    }
    else
    {
        fprintf(pfile, "bonus_hp : %d\n", world->player->bonus_hp);
        fprintf(pfile, "bonus_atk_power : %d\n", world->player->bonus_atk_power);
        fprintf(pfile, "bonus_atk_speed : %d", world->player->bonus_atk_speed);
        fclose(pfile);
    }
}