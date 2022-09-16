/**
 * \file test_update.c
 * \brief Programme testant les fonction implémentées dans update.c
 * \author YVOZ Ludovic
 * \author IOPETI Hugo
 * \date 24 Novembre 2020
 */

#include "../database.h"
#include "../init_and_clean.h"
#include "../events.h"
#include "../update.h"
#include "../player.h"
#include "../enemy.h"

/**
 * \brief Procédure qui teste l'initialisation et l'affichage d'un sprite
 * \param sprite le sprite à initialiser et à afficher
 * \param x la position du centre du sprite (sur l'abscisse)
 * \param y la position du centre du sprite (sur l'ordonnée)
 * \param h la hauteur du sprite
 * \param w la largueur du sprite
 * \param v la vitesse verticale du sprite
 */
void sprite_test_param(sprite_t *sprite, int x, int y, int w, int h, int v)
{
    int* w1 = malloc(sizeof(int)); //largeur du sprite 1
    w1[0] = w;
    init_sprite(sprite, x, y, w1, h, v);
    print_sprite(sprite);
}

/**
 * \brief Procédure qui créée des sprite à tester
 */
void sprite_test()
{
    sprite_t* sprite = malloc(sizeof(sprite_t));

    sprite_test_param(sprite, 10, 10, 22, 22, 69);
    sprite_test_param(sprite, 420, 420, 420, 420, 420);
}

/*Résultat attendu
x = 10
y = 10
h = 22
w = 22
v = 69
x = 420
y = 420
h = 420
w = 420
v = 420
*/

/**
 * \brief Procédure qui teste la fonction sprites_collide
 * \param sp1 sprite n°1
 * \param sp2 sprite n°2
 */
void sprites_collide_test_param(sprite_t *sp2, sprite_t *sp1)
{
    int test = sprites_collide(sp1, sp2);
    if (test == 1)
    {
        printf("Les deux sprites sont en collision !\n");
    }
    else
    {
        printf("Les deux sprites ne sont pas en collision !\n");
    }
    
}

/**
 * \brief Procédure qui teste la fonction sprites_collide
 */
void sprites_collide_test()
{
    sprite_t* sp1 = malloc(sizeof(sprite_t));
    sprite_t* sp2 = malloc(sizeof(sprite_t));
    sp1->h = PLAYER_HEIGHT;
    sp2->h = PLAYER_HEIGHT;

    //Test alors qu'ils ne sont pas en collision
    sp1->x = 0;
    sp1->y = 0;
    sp2->x = PLAYER_SPRITE_COLUMN_1_WIDTH + 6;
    sp2->y = PLAYER_HEIGHT + 9;
    sprites_collide_test_param(sp1, sp2);

    //Test alors qu'ils sont en collision
    sp2->x = 0;
    sp2->y = 0;
    sprites_collide_test_param(sp1, sp2);
}

/*Résultat attendu :
Les deux sprites ne sont pas en collision !
Les deux sprites sont en collision !
*/

/**
 *  \brief programme principal qui effectue les tests
 */
int main(int argc, char* args[])
{
    sprite_test();
    sprites_collide_test();
    return EXIT_SUCCESS;
}