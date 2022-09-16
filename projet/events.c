/**
 * \file events.c
 * \brief Programme définissant les fonctions déclarées dans events.h
 * \author YVOZ Ludovic
 * \author IOPETI Hugo
 * \date 27 mai 2020
 */

#include "events.h"

void handle_events(SDL_Event *event, world_t *world)
{
    float distance_x, distance_y;
    while (SDL_PollEvent(event))
    {
        switch (event->type)
        {
        case SDL_QUIT:
            world->gameover = 1;
            break;

        case SDL_KEYDOWN:
            switch (event->key.keysym.sym)
            {
            case SDLK_ESCAPE:
                //On mets en pause le jeu
                world->is_paused = 0;
                break;

            case SDLK_UP:
                //pareil que pour z
            case SDLK_z:
                //On fait avancer juste un peu le personnage car son mouvement sera complété lors de son animation
                world->player->sprite->y -= world->player->sprite->v / 7;
                //Le sprite est déjà le plus large, il n'est donc pas nécessaire de le changer
                if (sprite_is_out_of_bounds(world->player->sprite) == 0)
                {
                    if (sprite_is_out_of_additional_bounds(world->player->sprite, world->floor->direction, world->room_state) == 0)
                    {
                        world->player->sprite->y += world->player->sprite->v / 7;
                    }
                }

                //animation perso
                set_img_sprite(world->player->sprite, 6, 0);
                world->player->animation_timer = 1;

                //fin animation attaque
                set_invisible(world->player->atk_sprite_hori);
                set_invisible(world->player->atk_sprite_verti);
                break;

            case SDLK_DOWN:
            //pareil que pour s
            case SDLK_s:
                //On fait avancer juste un peu le personnage car son mouvement sera complété lors de son animation
                world->player->sprite->y += world->player->sprite->v / 7;
                //Je change temporairement le sprite en celui qui est le plus large sprite de marche pour éviter que le personnage reste coincé contre le mur dans certaines circonstances
                set_img_sprite(world->player->sprite, 6, world->player->sprite->wich_img[1]);
                if (sprite_is_out_of_bounds(world->player->sprite) == 0)
                {
                    if (sprite_is_out_of_additional_bounds(world->player->sprite, world->floor->direction, world->room_state) == 0)
                    {
                        world->player->sprite->y -= world->player->sprite->v / 7;
                    }
                }

                //animation perso
                set_img_sprite(world->player->sprite, 0, 0);
                world->player->animation_timer = 1;

                //fin animation attaque
                set_invisible(world->player->atk_sprite_hori);
                set_invisible(world->player->atk_sprite_verti);
                break;

            case SDLK_RIGHT:
            //pareil que pour d
            case SDLK_d:
                //On fait avancer juste un peu le personnage car son mouvement sera complété lors de son animation
                world->player->sprite->x += world->player->sprite->v / 7;
                //Je change temporairement le sprite en celui qui est le plus large sprite de marche pour éviter que le personnage reste coincé contre le mur dans certaines circonstances
                set_img_sprite(world->player->sprite, 6, world->player->sprite->wich_img[1]);
                if (sprite_is_out_of_bounds(world->player->sprite) == 0)
                {
                    if (sprite_is_out_of_additional_bounds(world->player->sprite, world->floor->direction, world->room_state) == 0)
                    {
                        world->player->sprite->x -= world->player->sprite->v / 7;
                    }
                }

                //animation perso
                set_img_sprite(world->player->sprite, 2, 0);
                world->player->animation_timer = 1;

                //fin animation attaque
                set_invisible(world->player->atk_sprite_hori);
                set_invisible(world->player->atk_sprite_verti);
                break;

            case SDLK_LEFT:
            //pareil que pour q
            case SDLK_q:
                //On fait avancer juste un peu le personnage car son mouvement sera complété lors de son animation
                world->player->sprite->x -= world->player->sprite->v / 7;
                //Je change temporairement le sprite en celui qui est le plus large sprite de marche pour éviter que le personnage reste coincé contre le mur dans certaines circonstances
                set_img_sprite(world->player->sprite, 6, world->player->sprite->wich_img[1]);
                if (sprite_is_out_of_bounds(world->player->sprite) == 0)
                {
                    if (sprite_is_out_of_additional_bounds(world->player->sprite, world->floor->direction, world->room_state) == 0)
                    {
                        world->player->sprite->x += world->player->sprite->v / 7;
                    }
                }

                //animation perso
                set_img_sprite(world->player->sprite, 4, 0);
                world->player->animation_timer = 1;

                //fin animation attaque
                set_invisible(world->player->atk_sprite_hori);
                set_invisible(world->player->atk_sprite_verti);
                break;

            case SDLK_SPACE:
                if (sprite_is_out_of_additional_bounds(world->player->sprite, world->floor->direction, world->room_state) == 1)
                {
                    //On passe à la prochaine salle si on n'est pas dans la dernière
                    if (world->floor->type == 0)
                    {
                        Liste_t *temp = world->floor;
                        world->floor = world->floor->suivant;
                        free(temp);
                        world->room_state = 0;
                        world->player->sprite->x = SCREEN_WIDTH / 2;
                        world->player->sprite->y = SCREEN_HEIGHT / 2;
                    }
                    else
                    { //On est dans la salle du boss
                        world->wants_reward = 0;
                    }
                }
                break;

            case SDLK_k:
                //augmente le bonus d'hp
                if (world->wants_reward == 0 && world->player->bonus_hp < 50)
                {
                    world->player->bonus_hp += 5;
                    world->gameover = 1;
                }
                break;

            case SDLK_l:
                //augmente le bonus d'attaque
                if (world->wants_reward == 0 && world->player->bonus_atk_power < 50)
                {
                    world->player->bonus_atk_power += 5;
                    world->gameover = 1;
                }
                break;

            case SDLK_m:
                //augmente le bonus de vitesse d'attaque
                if (world->wants_reward == 0 && world->player->bonus_atk_speed < 20)
                {
                    world->player->bonus_atk_speed += 2;
                    world->gameover = 1;
                }
                break;
            default:
                break;
            }

        case SDL_MOUSEBUTTONDOWN:
            switch (event->button.button)
            {
            case SDL_BUTTON_LEFT:
                //Le joueur effectue une attaque si il n'en a pas déjà effectué une il y peu selon sa vitesse d'attaque
                if (world->player->atk_speed_timer == 0)
                {
                    distance_x = sqrt(pow(world->player->sprite->x - event->motion.x, 2)); //La distance entre le "x" du joueur et le "x" de la souris
                    distance_y = sqrt(pow(world->player->sprite->y - event->motion.y, 2)); //La distance entre le "y" du joueur et le "y" de la souris

                    if (distance_x >= distance_y)
                    { //On sait que le curseur de la sourie est plus sur un des deux cotés du personnage que en bas ou en haut du personnage
                        if (event->motion.x <= world->player->sprite->x)
                        { //On sait que le curseur est à gauche du personnage
                            set_img_sprite(world->player->sprite, 5, 0);
                            world->player->animation_timer = 1;
                            world->player->atk_speed_timer = world->player->atk_speed;

                            //On fait apparaître l'attaque
                            set_img_sprite(world->player->atk_sprite_verti, 1, 0);
                            world->player->atk_sprite_verti->x = world->player->sprite->x - world->player->sprite->w[3] / 2 - world->player->atk_sprite_verti->w[1] * 2; //On fait apparaitre l'attaque en face du personnage
                            world->player->atk_sprite_verti->y = world->player->sprite->y;                                                                               //On fait apparaitre l'attaque en face du personnage
                            set_visible(world->player->atk_sprite_verti);

                            //On fait disparaitre les autres attaques en cas d'attaques rapides successives
                            set_invisible(world->player->atk_sprite_hori);
                        }
                        else
                        { //On sait que le curseur est à droite du personnage
                            set_img_sprite(world->player->sprite, 3, 0);
                            world->player->animation_timer = 1;
                            world->player->atk_speed_timer = world->player->atk_speed;

                            //On fait apparaître l'attaque
                            set_img_sprite(world->player->atk_sprite_verti, 0, 0);
                            world->player->atk_sprite_verti->x = world->player->sprite->x + world->player->sprite->w[3] / 2 + world->player->atk_sprite_verti->w[1] * 2; //On fait apparaitre l'attaque en face du personnage
                            world->player->atk_sprite_verti->y = world->player->sprite->y;                                                                               //On fait apparaitre l'attaque en face du personnage
                            set_visible(world->player->atk_sprite_verti);

                            //On fait disparaitre les autres attaques en cas d'attaques rapides successives
                            set_invisible(world->player->atk_sprite_hori);
                        }
                    }
                    else
                    {
                        if (event->motion.y <= world->player->sprite->y)
                        { //On sait que le curseur est en haut du personnage
                            set_img_sprite(world->player->sprite, 7, 0);
                            world->player->animation_timer = 1;
                            world->player->atk_speed_timer = world->player->atk_speed;

                            //On fait apparaître l'attaque
                            set_img_sprite(world->player->atk_sprite_hori, 1, 0);
                            world->player->atk_sprite_hori->x = world->player->sprite->x;                                                                        //On fait apparaitre l'attaque en face du personnage
                            world->player->atk_sprite_hori->y = world->player->sprite->y - world->player->sprite->h / 2 - world->player->atk_sprite_hori->h * 2; //On fait apparaitre l'attaque en face du personnage
                            set_visible(world->player->atk_sprite_hori);

                            //On fait disparaitre les autres attaques en cas d'attaques rapides successives
                            set_invisible(world->player->atk_sprite_verti);
                        }
                        else
                        { //On sait que le curseur est en bas du personnage
                            set_img_sprite(world->player->sprite, 1, 0);
                            world->player->animation_timer = 1;
                            world->player->atk_speed_timer = world->player->atk_speed;

                            //On fait apparaître l'attaque
                            set_img_sprite(world->player->atk_sprite_hori, 0, 0);
                            world->player->atk_sprite_hori->x = world->player->sprite->x;                                                                        //On fait apparaitre l'attaque en face du personnage
                            world->player->atk_sprite_hori->y = world->player->sprite->y + world->player->sprite->h / 2 + world->player->atk_sprite_hori->h * 2; //On fait apparaitre l'attaque en face du personnage
                            set_visible(world->player->atk_sprite_hori);

                            //On fait disparaitre les autres attaques en cas d'attaques rapides successives
                            set_invisible(world->player->atk_sprite_verti);
                        }
                    }
                }
                break;
                default:
                break;
            }
        }
    }
}

void handle_pause_events(SDL_Event *event, world_t *world)
{
    while (SDL_PollEvent(event))
    {
        switch (event->type)
        {
        case SDL_QUIT:
            //On finit la pause et on arrête le jeu
            world->is_paused = 1;
            world->gameover = 1;
            break;

        case SDL_KEYDOWN:
            switch (event->key.keysym.sym)
            {
            case SDLK_ESCAPE:
                //On finit la pause
                world->is_paused = 1;
                break;
                default:
                break;
            }
            default:
            break;
        }
    }
}

void handle_end_events(SDL_Event *event, world_t *world)
{
    while (SDL_PollEvent(event))
    {
        switch (event->type)
        {
        case SDL_QUIT:
            //Le joueur ne veut pas rejouer
            world->play_again = 0;
            break;
        case SDL_KEYDOWN:
            switch (event->key.keysym.sym)
            {
            case SDLK_ESCAPE:
                //Le joueur ne veut pas rejouer
                world->play_again = 0;
                break;
            case SDLK_SPACE:
                //Le joueur veut rejouer
                world->play_again = 1;
                world->gameover = 0;
                break;
                default:
                break;
            }
            default:
            break;
        }
    }
}