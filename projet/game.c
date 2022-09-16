/**
 * \file game.c
 * \brief Programme principal du jeu
 * \author YVOZ Ludovic
 * \author IOPETI Hugo
 * \date 23 Novembre 2020
 */
 
#include "database.h"
#include "graphique.h"
#include "events.h"
#include "init_and_clean.h"
#include "update.h"
#include "player.h"
#include "enemy.h"
#include "boss.h"

//#include "update.h" à venir


/**
* \brief fonction qui nettoie le jeu: nettoyage de la partie graphique (SDL), nettoyage des ressources, nettoyage des données
* \param window la fenêtre du jeu
* \param renderer le renderer
* \param resources les ressources
* \param world le monde
*/
void clean(SDL_Window *window, SDL_Renderer * renderer, resources_t *resources, world_t * world);


/**
 * \brief fonction qui initialise le jeu: initialisation de la partie graphique (SDL), chargement des ressources, initialisation des données
 * \param window la fenêtre du jeu
 * \param renderer le renderer
 * \param resources les ressources
 * \param world le monde
 */
void init(SDL_Window **window, SDL_Renderer ** renderer, resources_t *resources, world_t * world);


/**
 * \brief Fonction qui gère les animations
 * \param world le monde
 */
void handle_animations(world_t* world);


/**
 * \brief Fonction qui gère les timers
 * \param world le monde
 */
void handle_timers(world_t* world);


/**
 *  \brief programme principal qui implémente la boucle du jeu
 */
int main(int argc, char* args[]);


void clean(SDL_Window *window, SDL_Renderer * renderer, resources_t *resources, world_t * world){
    clean_data(world);
    clean_resources(resources);
    clean_sdl(renderer,window);
}


void init(SDL_Window **window, SDL_Renderer ** renderer, resources_t *resources, world_t * world){
    init_sdl(window,renderer,SCREEN_WIDTH, SCREEN_HEIGHT);
    init_ttf();
    init_data(world);
    init_resources(*renderer,resources);
}

void handle_animations(world_t* world) {
    handle_anim_player(world);
    if (world->floor->type == 1) {
        handle_anim_boss(world);
        handle_anim_boss_atk(world);
    }
}

void handle_timers(world_t* world) {
    handle_atk_speed_player(world);
    if (world->floor->type == 0) {
        handle_missile_timer(world);
    }
    else
    {
        handle_atk_speed_boss(world);
    }
}

int main(int argc, char* args[])
{
    SDL_Event event;
    world_t world;
    resources_t resources;
    SDL_Renderer *renderer;
    SDL_Window *window;

    //On vérifie si le joueur veut rejouer
    world.play_again = 1;
    while(world.play_again == 1) {
        //initialisation du jeu
        init(&window,&renderer,&resources,&world);

        //On affiche les images du début du jeu
        start_screen(renderer, &resources);

        while(!is_game_over(&world)){ //tant que le jeu n'est pas fini
            if (world.is_paused == 1) {
                //gestion des évènements
                handle_events(&event,&world);

                //mise à jour des données liée à la physique du monde
                update_data(&world);

                //Gestion des animations
                handle_animations(&world);

                //Gestion des données qui ont besoin d'un timer
                handle_timers(&world);
            
                //rafraichissement de l'écran
                refresh_graphics(renderer,&world,&resources);
            
                // pause de 10 ms pour controler la vitesse de rafraichissement
                SDL_Delay(10);
            } 
            else {
                //Le jeu est en pause
                pause_screen(&world, renderer, &resources);
                handle_pause_events(&event, &world);
                SDL_Delay(10);
            }
        }

        //On sauvegarde les bonus gagnés
        write_saved_file(&world);

        //On indique que le jeu va s'éteindre
        end_screen(&world, renderer, &resources);

        //On demande au joueur si il veut rejouer
        while (world.play_again == 2) {
            handle_end_events(&event, &world);
        }

        //nettoyage final
        clean(window,renderer,&resources,&world);
    }
    return 0;
}