/**
 * \file boss.C
 * \brief Programme définissant les fonctions déclarées dans boss.h
 * \author IOPETI Hugo
 * \author YVOZ Ludovic
 * \date 3 Janvier 2021
 */

#include "boss.h"

void init_boss(world_t *world)
{
    world->boss = malloc(sizeof(boss_t));
    world->boss->sprite = malloc(sizeof(sprite_t));
    world->boss->atk_sprite = malloc(sizeof(sprite_t));
}

void create_boss(world_t *world)
{
    int *w = malloc(sizeof(int) * NB_COLUMN_SPRITE_SHEET_BOSS);
    //On initialise les valeurs de w selon les largeurs des sprites dans la sprite sheet
    w[0] = BOSS_SPRITE_COLUMN_1_6_WIDTH;
    w[1] = BOSS_SPRITE_COLUMN_2_5_WIDTH;
    w[2] = BOSS_SPRITE_COLUMN_3_4_WIDTH;
    w[3] = BOSS_SPRITE_COLUMN_3_4_WIDTH;
    w[4] = BOSS_SPRITE_COLUMN_2_5_WIDTH;
    w[5] = BOSS_SPRITE_COLUMN_1_6_WIDTH;

    init_sprite(world->boss->sprite, SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2, w, BOSS_HEIGHT, BOSS_SPEED);
    set_img_sprite(world->player->sprite, 2, 0); //On affiche l'image de repos du boss en premier

    //On initialise l'attaque du personnage
    int *atk_w = malloc(sizeof(int) * NB_COLUMN_SPRITE_SHEET_BOSS_ATTACK);
    atk_w[0] = BOSS_ATTACK_SPRITE_COLUMN_1_2_15_16_WIDTH;
    atk_w[1] = BOSS_ATTACK_SPRITE_COLUMN_1_2_15_16_WIDTH;
    atk_w[2] = BOSS_ATTACK_SPRITE_COLUMN_3_14_WIDTH;
    atk_w[3] = BOSS_ATTACK_SPRITE_COLUMN_4_6_11_13_WIDTH;
    atk_w[4] = BOSS_ATTACK_SPRITE_COLUMN_5_12_WIDTH;
    atk_w[5] = BOSS_ATTACK_SPRITE_COLUMN_4_6_11_13_WIDTH;
    atk_w[6] = BOSS_ATTACK_SPRITE_COLUMN_7_10_WIDTH;
    atk_w[7] = BOSS_ATTACK_SPRITE_COLUMN_8_9_WIDTH;
    atk_w[8] = BOSS_ATTACK_SPRITE_COLUMN_8_9_WIDTH;
    atk_w[9] = BOSS_ATTACK_SPRITE_COLUMN_7_10_WIDTH;
    atk_w[10] = BOSS_ATTACK_SPRITE_COLUMN_4_6_11_13_WIDTH;
    atk_w[11] = BOSS_ATTACK_SPRITE_COLUMN_5_12_WIDTH;
    atk_w[12] = BOSS_ATTACK_SPRITE_COLUMN_4_6_11_13_WIDTH;
    atk_w[13] = BOSS_ATTACK_SPRITE_COLUMN_3_14_WIDTH;
    atk_w[14] = BOSS_ATTACK_SPRITE_COLUMN_1_2_15_16_WIDTH;
    atk_w[15] = BOSS_ATTACK_SPRITE_COLUMN_1_2_15_16_WIDTH;
    init_sprite(world->boss->atk_sprite, 0, 0, atk_w, BOSS_ATTACK_HEIGHT, 0);
    set_invisible(world->boss->atk_sprite);

    world->boss->hp = BOSS_HP;
    world->boss->atk_power = BOSS_ATK_POWER;
    world->boss->atk_speed = BOSS_ATK_POWER;
    world->boss->atk_speed_timer = 0;
    world->boss->animation_timer = 0;
    world->boss->atk_animation_timer = 0;
    world->boss->invincibility_timer = 0;
    world->boss->is_invincible = 1;
}

void update_boss(world_t *world)
{
    //Le boss finit d'abord son action avant d'en commencer une autre
    if (world->boss->animation_timer == 0 && world->boss->sprite->is_visible == 0)
    {
        //Le boss attaque le joueur plutot qu'avancer si le joueur est assez proche et si la vitesse d'attaque du boss lui le permet
        if (world->boss->atk_speed_timer == 0 && world->boss->sprite->x - world->player->sprite->x >= -ATK_DISTANCE_X && world->boss->sprite->x - world->player->sprite->x <= ATK_DISTANCE_X && world->boss->sprite->y - world->player->sprite->y >= -ATK_DISTANCE_Y && world->boss->sprite->y - world->player->sprite->y <= ATK_DISTANCE_Y)
        {
            //Le boss attaque dans la direction du joueur
            if (world->player->sprite->x > world->boss->sprite->x)
            {
                set_img_sprite(world->boss->sprite, 0, 0);
                world->boss->atk_sprite->x = world->boss->sprite->x + world->boss->sprite->w[0] / 2 + world->boss->atk_sprite->w[2] / 2;
                world->boss->atk_sprite->y = world->boss->sprite->y;
                set_visible(world->boss->atk_sprite);
                set_img_sprite(world->boss->atk_sprite, 0, 0);
                world->boss->atk_speed_timer = world->boss->atk_speed;
                world->boss->atk_animation_timer = 1;
                //On lance les animations du boss
                world->boss->animation_timer = 1;
            }
            else
            {
                set_img_sprite(world->boss->sprite, 5, 0);
                world->boss->atk_sprite->x = world->boss->sprite->x - world->boss->sprite->w[5] / 2 - world->boss->atk_sprite->w[2];
                world->boss->atk_sprite->y = world->boss->sprite->y;
                set_visible(world->boss->atk_sprite);
                set_img_sprite(world->boss->atk_sprite, 15, 0);
                world->boss->atk_speed_timer = world->boss->atk_speed;
                world->boss->atk_animation_timer = 1;
                //On lance les animations du boss
                world->boss->animation_timer = 1;
            }
        }
        else
        { //Le boss se déplace si le joueur n'est pas à portée
            int slow_animation = generate_number(1, 5);
            if (slow_animation == 1)
            {
                //On fait avancer le boss vers le joueur verticalement
                if (world->player->sprite->y > world->boss->sprite->y)
                {
                    world->boss->sprite->y += world->boss->sprite->v / 4;
                    if (sprite_is_out_of_bounds(world->boss->sprite) == 0)
                    {
                        world->boss->sprite->y -= world->boss->sprite->v / 4;
                    }
                    //On lance les animations du boss
                    world->boss->animation_timer = 1;
                }
                else
                {
                    world->boss->sprite->y -= world->boss->sprite->v / 4;
                    if (sprite_is_out_of_bounds(world->boss->sprite) == 0)
                    {
                        world->boss->sprite->y += world->boss->sprite->v / 4;
                    }
                    //On lance les animations du boss
                    world->boss->animation_timer = 1;
                }
                //On fait avancer le boss vers le joueur horizontalement
                if (world->player->sprite->x > world->boss->sprite->x)
                {
                    world->boss->sprite->x += world->boss->sprite->v / 4;
                    if (sprite_is_out_of_bounds(world->boss->sprite) == 0)
                    {
                        world->boss->sprite->x -= world->boss->sprite->v / 4;
                    }
                    set_img_sprite(world->boss->sprite, 2, 0);
                    //On lance les animations du boss
                    world->boss->animation_timer = 1;
                }
                else
                {
                    world->boss->sprite->x -= world->boss->sprite->v / 4;
                    if (sprite_is_out_of_bounds(world->boss->sprite) == 0)
                    {
                        world->boss->sprite->x += world->boss->sprite->v / 4;
                    }
                    set_img_sprite(world->boss->sprite, 3, 0);
                    //On lance les animations du boss
                    world->boss->animation_timer = 1;
                }
            }
        }
    }
}

void handle_anim_boss(world_t *world)
{
    if (world->boss->animation_timer >= 1 && world->boss->animation_timer < 25)
    { //25 = 3*8 + 1 car on fait un changement de sprite toutes les 8 boucles de jeu pour une animation moins rapide et on a 4 sprites dans une animation (notés de 0 à 3)
        if (world->boss->animation_timer % 8 == 0)
        {
            world->boss->sprite->wich_img[1]++;
            //On fait avancer le boss si il en train d'avancer
            switch (world->boss->sprite->wich_img[0])
            {
            case 2:
                //Pareil qu'en dessous

            case 3:
                //On fait avancer le boss vers le joueur verticalement
                if (world->player->sprite->y > world->boss->sprite->y)
                {
                    world->boss->sprite->y += world->boss->sprite->v / 4;
                    if (sprite_is_out_of_bounds(world->boss->sprite) == 0)
                    {
                        world->boss->sprite->y -= world->boss->sprite->v / 4;
                    }
                }
                else
                {
                    world->boss->sprite->y -= world->boss->sprite->v / 4;
                    if (sprite_is_out_of_bounds(world->boss->sprite) == 0)
                    {
                        world->boss->sprite->y += world->boss->sprite->v / 4;
                    }
                }
                //On fait avancer le boss vers le joueur horizontalement
                if (world->player->sprite->x > world->boss->sprite->x)
                {
                    world->boss->sprite->x += world->boss->sprite->v / 4;
                    if (sprite_is_out_of_bounds(world->boss->sprite) == 0)
                    {
                        world->boss->sprite->x -= world->boss->sprite->v / 4;
                    }
                }
                else
                {
                    world->boss->sprite->x -= world->boss->sprite->v / 4;
                    if (sprite_is_out_of_bounds(world->boss->sprite) == 0)
                    {
                        world->boss->sprite->x += world->boss->sprite->v / 4;
                    }
                }
                break;
                default:
                break;
            }
        }
        world->boss->animation_timer++;
    }
    else
    {
        world->boss->animation_timer = 0;
        if (world->boss->hp <= 0)
        {
            set_invisible(world->boss->sprite);
        }
        set_img_sprite(world->boss->sprite, world->boss->sprite->wich_img[0], 0); //On remet le sprite dans une position détente après son attaque ou après son déplacement
    }
}

void handle_anim_boss_atk(world_t *world)
{
    if (world->boss->atk_animation_timer >= 1 && world->boss->atk_animation_timer < 29)
    { //29 = 7*4 + 1 car on fait un changement de sprite toutes les 4 boucles de jeu pour une animation moyenne et on a 8 sprites dans une animation (notés de 0 à 7)
        if (world->boss->atk_animation_timer % 4 == 0)
        {
            //Comme la sprite sheet à été conçue en miroir il faut savoir où nous nous trouvons dessus pour l'animation
            if (world->boss->atk_sprite->wich_img[0] <= 7)
            { //Nous sommes du côté gauche de la sprite sheet
                world->boss->atk_sprite->wich_img[0]++;
            }
            else
            { //Nous sommes du côté droit de la sprite sheet
                world->boss->atk_sprite->wich_img[0]--;
            }
        }
        world->boss->atk_animation_timer++;
    }
    else
    {
        world->boss->atk_animation_timer = 0;
        set_invisible(world->boss->atk_sprite);
    }
}

void handle_atk_speed_boss(world_t *world)
{
    if (world->boss->atk_speed_timer >= 1 && world->boss->atk_speed_timer < 75)
    {
        world->boss->atk_speed_timer++;
    }
    else
    {
        world->boss->atk_speed_timer = 0;
    }
}

void free_boss(world_t *world)
{
    if (world->floor->type == 1)
    {
        free(world->boss->sprite->w);
        free(world->boss->sprite->wich_img);
        free(world->boss->atk_sprite->w);
        free(world->boss->atk_sprite->wich_img);
    }
    free(world->boss->sprite);
    free(world->boss->atk_sprite);
    free(world->boss);
}