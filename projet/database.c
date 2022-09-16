/**
 * \file database.c
 * \brief Programme definissant les fonctions déclarées dans database.h
 * \author YVOZ Ludovic
 * \author IOPETI Hugo
 * \date 12 novembre 2020
 */
#include "database.h"

void init_sprite(sprite_t *sprite, int x, int y, int *w, int h, int v)
{
    sprite->x = x;
    sprite->y = y;
    sprite->h = h;
    sprite->w = w;
    sprite->v = v;
    sprite->is_visible = 0;
    sprite->wich_img = malloc(sizeof(int) * 2);
    sprite->wich_img[0] = 0;
    sprite->wich_img[1] = 0;
}

int generate_number(int a, int b)
{
    return rand() % (b - a) + a;
}

void set_visible(sprite_t *sprite)
{
    sprite->is_visible = 0;
}

void set_invisible(sprite_t *sprite)
{
    sprite->is_visible = 1;
}

int is_game_over(world_t *world)
{
    return world->gameover;
}

int sprite_is_out_of_bounds(sprite_t *sprite)
{
    if ((sprite->x + sprite->w[sprite->wich_img[0]] / 2 >= PLAY_ZONE_RIGHT_WALL) || (sprite->x - sprite->w[sprite->wich_img[0]] / 2 <= PLAY_ZONE_LEFT_WALL) || (sprite->y <= PLAY_ZONE_TOP_WALL) || (sprite->y + sprite->h / 2 >= PLAY_ZONE_BOTTOM_WALL))
    { //Pour le haut, on mets la limite à la moitié du sprite car le haut du joueur peut apparaître sur le mur du haut
        return 0;
    }
    return 1;
}

int sprite_is_out_of_additional_bounds(sprite_t *sprite, int direction, int room_state)
{
    if (room_state != 1)
    {
        switch (direction)
        {
        case 0:
            if ((sprite->x + sprite->w[sprite->wich_img[0]] / 2 <= PLAY_ZONE_ADD_TOP_BOT_X_2 - WALL_WIDTH - POST_WIDTH) && (sprite->x - sprite->w[sprite->wich_img[0]] / 2 >= PLAY_ZONE_ADD_TOP_X + 1 + WALL_WIDTH + POST_WIDTH) && (sprite->y + sprite->h / 2 >= PLAY_ZONE_BOTTOM_WALL - 10) && (sprite->y + sprite->h / 2 <= SCREEN_HEIGHT))
            { //On regarde si le joueur est dans le couloir en bas quand tous les monstres sont morts
                return 1;
            }
            break;

        case 1:
            if ((sprite->x + sprite->w[sprite->wich_img[0]] / 2 <= SCREEN_WIDTH) && (sprite->x - sprite->w[sprite->wich_img[0]] / 2 >= PLAY_ZONE_RIGHT_WALL - 40) && (sprite->y + sprite->h / 2 >= PLAY_ZONE_ADD_LEFT_Y + 1 + WALL_WITDH_LEFT) && (sprite->y + sprite->h / 2 <= PLAY_ZONE_ADD_LEFT_RIGHT_Y_2 - WALL_WITDH_LEFT_2))
            { //On regarde si le joueur est dans le couloir à droite quand tous les monstres sont mort
                return 1;
            }
            break;

        case 2:
            if ((sprite->x + sprite->w[sprite->wich_img[0]] / 2 <= PLAY_ZONE_LEFT_WALL + 40) && (sprite->x - sprite->w[sprite->wich_img[0]] / 2 >= 0) && (sprite->y + sprite->h / 2 >= PLAY_ZONE_ADD_LEFT_Y + WALL_WITDH_LEFT) & (sprite->y + sprite->h / 2 <= PLAY_ZONE_ADD_LEFT_RIGHT_Y_2 - WALL_WITDH_LEFT_2))
            { //On regarde si le joueur est dans le couloir à gauche quand tous les monstres sont mort
                return 1;
            }
            break;

        case 3:
            if ((sprite->x + sprite->w[sprite->wich_img[0]] / 2 <= PLAY_ZONE_ADD_TOP_BOT_X_2 - WALL_WIDTH - POST_WIDTH) && (sprite->x - sprite->w[sprite->wich_img[0]] / 2 >= PLAY_ZONE_ADD_TOP_X + WALL_WIDTH + POST_WIDTH) && (sprite->y - sprite->h / 2 >= 0) && (sprite->y + sprite->h / 2 <= PLAY_ZONE_TOP_WALL + 20))
            { //On regarde si le joueur est dans le couloir en haut quand tous les monstres sont mort
                return 1;
            }
            break;
            default:
            break;
        }
        return 0;
    }
    return 0;
}

void set_img_sprite(sprite_t *sprite, int x, int y)
{
    sprite->wich_img[0] = x;
    sprite->wich_img[1] = y;
}