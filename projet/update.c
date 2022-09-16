/**
 * \file update.c
 * \brief Programme définissant les fonctions déclarées dans update.h
 * \author YVOZ Ludovic
 * \author IOPETI Hugo
 * \date 24 Novembre 2020
 */

#include "update.h"

void update_data(world_t *world){
    //On sépare le fait d'être dans une salle de boss ou pas
    if (world->floor->type == 0) {
        if (world->room_state == 0) {   //On génère de nouveaux monstres si on est dans une nouvelle salle
            create_enemies(world);
            create_missiles(world);
            world->player->is_invincible = 0;   //On rends le joueur invincible quand il rentre dans une salle pour éviter de mourir sans pouvoir réagir
            world->player->invincibility_timer = 1;
            world->room_state = 1;
        } 

        //On gère les attaques du personnage et des ennemis
        handle_attacks(world);
        handle_invincibility(world);

        //On gère le fait de finir une salle
        if (world->room_state == 1 && nb_enemies_alive(world) == 0) {
            world->room_state = 2;
        }

        update_enemies(world);
        update_missiles(world);
    }
    else {  //On est dans la salle du boss
        if (world->room_state == 0) {   //On génère le boss quand on arrive dans la salle du boss
            create_boss(world);
            world->player->is_invincible = 0;   //On rends le joueur invincible quand il rentre dans une salle pour éviter de mourir sans pouvoir réagir
            world->player->invincibility_timer = 1;
            world->room_state = 1;
        }

        //On gère les attaques du boss et du joueur
        handle_boss_attacks(world);
        handle_boss_invincibility(world);

        //On gère le fait de finir une salle
        if (world->room_state == 1 && world->boss->sprite->is_visible == 1) {
            world->room_state = 2;
        }

        update_boss(world);
    }
}

int sprites_collide(sprite_t *sp2, sprite_t *sp1)
{
    if (sp1->x + sp1->w[sp1->wich_img[0]]/2 >= sp2->x - sp2->w[sp2->wich_img[0]]/2 && sp1->x - sp1->w[sp1->wich_img[0]]/2 <= sp2->x + sp2->w[sp2->wich_img[0]]/2 && sp1->y - sp1->h/2 <= sp2->y + sp2->h/2 && sp1->y + sp1->h/2 >= sp2->y - sp2->h/2) {
        return 1;
    }
    return 0;
}

void handle_attacks(world_t* world) {
    for (int i = 0; i < world->nb_enemies; i++) {

        //On gère le fait que le joueur attaque un monstre
        if (world->enemies[i]->sprite->is_visible == 0 && world->enemies[i]->is_invincible == 1) {
            if ((sprites_collide(world->player->atk_sprite_hori, world->enemies[i]->sprite) == 1 && world->player->atk_sprite_hori->is_visible == 0) || (sprites_collide(world->player->atk_sprite_verti, world->enemies[i]->sprite) == 1 && world->player->atk_sprite_verti->is_visible == 0)) {
                world->enemies[i]->hp -= world->player->atk_power;
                if (world->enemies[i]->hp <= 0) {
                    set_invisible(world->enemies[i]->sprite);
                    //Si une tourelle meurt, son missile disparait avec
                    if (world->enemies[i]->type == 3) {
                        for (int j = 0; j < world->nb_missiles; j++) {
                            if (world->missiles[j]->nb_turret == i) {
                                set_invisible(world->missiles[j]->sprite);
                            }
                        }
                    }
                }
                //On le rends invincible pendant un cours instant pour éviter que le joueur abuse de sa vitesse d'attaque
                world->enemies[i]->is_invincible = 0;
                world->enemies[i]->invincibility_timer = 1;   
            }
        }

        //On gère le fait qu'un monstre attaque le joueur
        if(sprites_collide(world->enemies[i]->sprite, world->player->sprite) == 1 && world->enemies[i]->sprite->is_visible == 0 && world->player->is_invincible == 1) {
            world->player->hp -= world->enemies[i]->atk_power;
            if (world->player->hp <= 0) {
                world->gameover = 1;
            }
            //On le rends invincible pendant un court instant pour simuler la vitesse d'attaque des monstres
            world->player->is_invincible = 0;
            world->player->invincibility_timer = world->enemies[i]->atk_speed; 
        }
    }

    
    for (int i = 0; i < world->nb_missiles; i++) {
    //On gère le fait que le joueur attaque un missile
        if (world->missiles[i]->sprite->is_visible == 0) {
            if ((sprites_collide(world->player->atk_sprite_hori, world->missiles[i]->sprite) == 1 && world->player->atk_sprite_hori->is_visible == 0) || (sprites_collide(world->player->atk_sprite_verti, world->missiles[i]->sprite) == 1 && world->player->atk_sprite_verti->is_visible == 0)) {
                set_invisible(world->missiles[i]->sprite);
                world->missiles[i]->timer_missile = 1;  //On reset le timer du missile pour que le joueur ait le temps de s'approcher des tourelles
            }
        }

        //On gère le fait qu'un missile touche le joueur
        if (sprites_collide(world->player->sprite, world->missiles[i]->sprite) == 1 && world->player->is_invincible == 1 && world->missiles[i]->sprite->is_visible == 0) {
            world->player->hp -= world->missiles[i]->atk_power;
            set_invisible(world->missiles[i]->sprite);
            world->missiles[i]->timer_missile = 1;  //On reset le timer du missile pour que le joueur ait le temps de s'approcher des tourelles
            if (world->player->hp <= 0) {
                world->gameover = 1;
            }
            //On le rends invincible pendant un court instant pour simuler la vitesse d'attaque des monstres
            world->player->is_invincible = 0;
            world->player->invincibility_timer = 1; //Le joueur est invincible pendant pas mal de temps car il à pris un gros coup
        }   
    }
}

void handle_boss_attacks(world_t* world) {
    //On gère le fait que le joueur attaque le boss
    if (world->boss->sprite->is_visible == 0 && world->boss->is_invincible == 1) {
        if ((sprites_collide(world->player->atk_sprite_hori, world->boss->sprite) == 1 && world->player->atk_sprite_hori->is_visible == 0) || (sprites_collide(world->player->atk_sprite_verti, world->boss->sprite) == 1 && world->player->atk_sprite_verti->is_visible == 0)) {
            world->boss->hp -= world->player->atk_power;
            if (world->boss->hp <= 0) {
                if (world->boss->sprite->wich_img[0] < 3) {
                    set_img_sprite(world->boss->sprite, 1, 0);
                    world->boss->animation_timer = 1;
                }
                else {
                    set_img_sprite(world->boss->sprite, 4, 0);
                    world->boss->animation_timer = 1;
                } 
            }
            //On le rends invincible pendant un cours instant pour éviter que le joueur abuse de sa vitesse d'attaque
            world->boss->is_invincible = 0;
            world->boss->invincibility_timer = 1;   
        }
    }

    //On gère le fait que le boss attaque le joueur
    if (sprites_collide(world->player->sprite, world->boss->sprite) == 1 && world->player->is_invincible == 1 && world->boss->sprite->is_visible == 0) {
        world->player->hp -= world->boss->atk_power*2;
        if (world->player->hp <= 0) {
            world->gameover = 1;
        }
        //On le rends invincible pendant un court instant pour simuler la vitesse d'attaque du boss
        world->player->is_invincible = 0;
        world->player->invincibility_timer = 1; //Le joueur est invincible pendant pas mal de temps car il à pris un gros coup
    }

    //On gère le fait que l'attaque du boss frappe le joueur
    if (sprites_collide(world->player->sprite, world->boss->atk_sprite) == 1 && world->player->is_invincible == 1 && world->boss->atk_sprite->is_visible == 0) {
        world->player->hp -= world->boss->atk_power;
        set_invisible(world->boss->atk_sprite);
        if (world->player->hp <= 0) {
            world->gameover = 1;
        }
        //On le rends invincible pendant un court instant pour simuler la vitesse d'attaque du boss
        world->player->is_invincible = 0;
        world->player->invincibility_timer = 1; //Le joueur est invincible pendant pas mal de temps car il à pris un gros coup
    }  
}

void handle_invincibility(world_t* world) {
    //On gère l'invicibilité du joueur
    if (world->player->invincibility_timer >= 1 && world->player->invincibility_timer <= 150) {
        world->player->invincibility_timer += 1;
    }
    else {
        world->player->invincibility_timer = 0;
        world->player->is_invincible = 1;
    }

    //On gère l'invicibilité des monstres
    for (int i = 0; i < world->nb_enemies; i++) {
        if (world->enemies[i]->invincibility_timer >= 1 && world->enemies[i]->invincibility_timer < 22) { //Presque le même temps que les attaques du joueur restent à l'écran pour ne pas prendre plusieurs coups avec une seule attaque
            world->enemies[i]->invincibility_timer += 1;
        }
        else {
            world->enemies[i]->invincibility_timer = 0;
            world->enemies[i]->is_invincible = 1;
        }
    }
}

void handle_boss_invincibility(world_t* world) {
    //On gère l'invicibilité du boss
    if (world->boss->invincibility_timer >= 1 && world->boss->invincibility_timer < 22) { //Presque le même temps que les attaques du joueur restent à l'écran pour ne pas prendre plusieurs coups avec une seule attaque
        world->boss->invincibility_timer += 1;
    }
    else {
        world->boss->invincibility_timer = 0;
        world->boss->is_invincible = 1;
    }

    //On gère l'invicibilité du joueur
    if (world->player->invincibility_timer >= 1 && world->player->invincibility_timer <= 150) {
        world->player->invincibility_timer += 1;
    }
    else {
        world->player->invincibility_timer = 0;
        world->player->is_invincible = 1;
    }
}

void print_sprite(sprite_t * sprite)
{
    printf("x = %d\ny = %d\nh = %d\nw = %d\nv = %d\n",
        sprite->x,sprite->y,sprite->h,sprite->w[sprite->wich_img[0]],sprite->v);
}

int nb_enemies_alive(world_t* world) {
    int nb_enemies_alive = 0;
    for (int i = 0; i < world->nb_enemies; i++) {
        if (world->enemies[i]->sprite->is_visible == 0) {
            nb_enemies_alive++;
        }
    }
    return nb_enemies_alive;
}