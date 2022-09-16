/**
 * \file enemy.C
 * \brief Programme définnissant les fonctions déclarées dans enemy.h
 * \author IOPETI Hugo
 * \author YVOZ Ludovic
 * \date 24 novembre 2020
 */

#include "enemy.h"

void init_enemies(world_t *world)
{
    world->enemies = malloc(sizeof(monster_t *) * NB_ENEMIES_MAX);
    for (int i = 0; i < NB_ENEMIES_MAX; i++)
    {
        world->enemies[i] = malloc(sizeof(monster_t));
        world->enemies[i]->sprite = malloc(sizeof(sprite_t));
    }
    world->nb_enemies_max = 5; //Nombre d'ennemis maximum pour la première salle
    world->nb_enemies_min = 2; //Nombre d'ennemis minimum pour la première salle
}

void create_enemies(world_t *world)
{
    world->nb_enemies = generate_number(world->nb_enemies_min, world->nb_enemies_max);

    int type, x_temp, y_temp, too_close;
    int *w1 = malloc(sizeof(int)); //largeur du monstre 1
    w1[0] = ENEMY_1_WIDTH;
    int *w2 = malloc(sizeof(int)); //largeur du monstre 2
    w2[0] = ENEMY_2_WIDTH;
    int *w3 = malloc(sizeof(int)); //largeur du monstre 3
    w3[0] = ENEMY_3_WIDTH;
    for (int i = 0; i < world->nb_enemies; i++)
    {

        //On gère la création de certains type de monstres
        switch (world->nb_enemies_min)
        {
        case 2:
            type = 1; // Que des slimes pour la première salle
            break;

        case 3:
            type = generate_number(1, 3); //Que des slimes et des crânes pour la deuxième salle
            break;

        default:
            type = generate_number(1, 4); // 3 ennemis différents pour les autres salles
            break;
        }

        //On gère le fait de faire apparaitre les monstres au hasard sur l'écran et également le fait qu'un monstre ne peut pas apparaîte trop près du joueur
        too_close = 0;
        while (too_close == 0)
        {
            x_temp = generate_number(PLAY_ZONE_LEFT_WALL + ENEMY_1_WIDTH / 2, PLAY_ZONE_RIGHT_WALL - ENEMY_1_WIDTH / 2);   //largeur du plus large monstre
            y_temp = generate_number(PLAY_ZONE_TOP_WALL + ENEMY_1_HEIGHT / 2, PLAY_ZONE_BOTTOM_WALL - ENEMY_2_HEIGHT / 2); //hauteur du plus grand monstre
            if (!(x_temp < SCREEN_WIDTH / 2 + SPAWN_DISTANCE && x_temp > SCREEN_WIDTH / 2 - SPAWN_DISTANCE && y_temp < SCREEN_HEIGHT / 2 + SPAWN_DISTANCE && y_temp > SCREEN_HEIGHT / 2 - SPAWN_DISTANCE))
            {
                too_close = 1;
            }
        }

        switch (type)
        {
        case 1:
            init_sprite(world->enemies[i]->sprite, x_temp, y_temp, w1, ENEMY_1_HEIGHT, ENEMY_1_SPEED);
            world->enemies[i]->hp = ENEMY_1_HP;
            world->enemies[i]->atk_power = ENEMY_1_ATK_POWER;
            world->enemies[i]->atk_speed = ENEMY_1_ATK_SPEED;
            break;

        case 2:
            init_sprite(world->enemies[i]->sprite, x_temp, y_temp, w2, ENEMY_2_HEIGHT, ENEMY_2_SPEED);
            world->enemies[i]->hp = ENEMY_2_HP;
            world->enemies[i]->atk_power = ENEMY_2_ATK_POWER;
            world->enemies[i]->atk_speed = ENEMY_2_ATK_SPEED;
            break;

        case 3:
            init_sprite(world->enemies[i]->sprite, x_temp, y_temp, w3, ENEMY_3_HEIGHT, ENEMY_3_SPEED);
            world->enemies[i]->hp = ENEMY_3_HP;
            world->enemies[i]->atk_power = ENEMY_3_ATK_POWER;
            world->enemies[i]->atk_speed = ENEMY_3_ATK_SPEED;
            break;
            default:
            break;
        }
        world->enemies[i]->invincibility_timer = 0;
        world->enemies[i]->is_invincible = 1;
        world->enemies[i]->type = type;
    }

    world->nb_enemies_min++;
    world->nb_enemies_max++;
}

void init_missiles(world_t *world)
{
    world->missiles = malloc(sizeof(missile_t *) * NB_ENEMIES_MAX);
    for (int i = 0; i < NB_ENEMIES_MAX; i++)
    {
        world->missiles[i] = malloc(sizeof(missile_t));
        world->missiles[i]->sprite = malloc(sizeof(sprite_t));
    }
}

void create_missiles(world_t *world)
{
    world->nb_missiles = 0;
    int *w = malloc(sizeof(int));
    w[0] = MISSILE_WIDTH;
    for (int i = 0; i < world->nb_enemies; i++)
    {
        if (world->enemies[i]->type == 3)
        {
            init_sprite(world->missiles[world->nb_missiles]->sprite, world->enemies[i]->sprite->x, world->enemies[i]->sprite->y, w, MISSILE_HEIGHT, MISSILE_SPEED);
            set_invisible(world->missiles[world->nb_missiles]->sprite);
            world->missiles[world->nb_missiles]->nb_turret = i;
            world->missiles[world->nb_missiles]->atk_power = MISSILE_ATK_POWER;
            world->missiles[world->nb_missiles]->timer_missile = 200;
            world->nb_missiles++;
        }
    }
}

void free_enemies(world_t *world)
{
    for (int i = 0; i < NB_ENEMIES_MAX; i++)
    {
        free(world->enemies[i]->sprite);
        free(world->enemies[i]);
    }
    free(world->enemies);
}

void free_missiles(world_t *world)
{
    for (int i = 0; i < NB_ENEMIES_MAX; i++)
    {
        free(world->missiles[i]->sprite);
        free(world->missiles[i]);
    }
    free(world->missiles);
}

void update_enemies(world_t *world)
{
    for (int i = 0; i < world->nb_enemies; ++i)
    {
        if (world->enemies[i]->type == 1)
        {                                                //Déplacement des slimes
            int speed_restraint = generate_number(1, 4); //On donne une chance sur trois aux slimes d'avancer pour qu'ils ne soient pas trop rapides et pour qu'ils n'avancent pas tous à la même vitesse
            if (speed_restraint == 1)
            {
                //On fait avancer les monstres vers le joueur
                if (world->player->sprite->x > world->enemies[i]->sprite->x)
                {
                    world->enemies[i]->sprite->x += world->enemies[i]->sprite->v;
                }
                else
                {
                    world->enemies[i]->sprite->x -= world->enemies[i]->sprite->v;
                }
                if (world->player->sprite->y > world->enemies[i]->sprite->y)
                {
                    world->enemies[i]->sprite->y += world->enemies[i]->sprite->v;
                }
                else
                {
                    world->enemies[i]->sprite->y -= world->enemies[i]->sprite->v;
                }
            }
        }
        else
        { //Déplacement des cranes
            world->enemies[i]->sprite->y += world->enemies[i]->sprite->v;
            if (sprite_is_out_of_bounds(world->enemies[i]->sprite) == 0)
            {
                world->enemies[i]->sprite->v = -world->enemies[i]->sprite->v;
                world->enemies[i]->sprite->y += world->enemies[i]->sprite->v;
                world->enemies[i]->sprite->wich_img[1] = (world->enemies[i]->sprite->wich_img[1] + 1) % 2;
            }
        }
    }
}

void update_missiles(world_t *world)
{
    for (int i = 0; i < world->nb_missiles; i++)
    {
        if (world->missiles[i]->sprite->is_visible == 1 && world->enemies[world->missiles[i]->nb_turret]->sprite->is_visible == 0 && world->missiles[i]->timer_missile >= 200)
        { //Si le missile précédent est détruit, on le fait réapparaitre
            world->missiles[i]->sprite->x = world->enemies[world->missiles[i]->nb_turret]->sprite->x;
            world->missiles[i]->sprite->y = world->enemies[world->missiles[i]->nb_turret]->sprite->y;
            world->missiles[i]->target_x = world->player->sprite->x;
            world->missiles[i]->target_y = world->player->sprite->y;
            world->missiles[i]->timer_missile = 0;
            set_visible(world->missiles[i]->sprite);
        }
        else
        {
            //Le missile se dirige vers sa cible
            if (world->missiles[i]->target_x > world->missiles[i]->sprite->x)
            {
                world->missiles[i]->sprite->x += world->missiles[i]->sprite->v;
            }
            else
            {
                world->missiles[i]->sprite->x -= world->missiles[i]->sprite->v;
            }
            if (world->missiles[i]->target_y > world->missiles[i]->sprite->y)
            {
                world->missiles[i]->sprite->y += world->missiles[i]->sprite->v;
            }
            else
            {
                world->missiles[i]->sprite->y -= world->missiles[i]->sprite->v;
            }
        }
    }
}

void handle_missile_timer(world_t *world)
{
    for (int i = 0; i < world->nb_missiles; i++)
    {
        if (world->missiles[i]->timer_missile < 200)
        {
            world->missiles[i]->timer_missile++;
        }
        else
        {
            set_invisible(world->missiles[i]->sprite);
        }
    }
}