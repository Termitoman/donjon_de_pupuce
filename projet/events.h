/**
 * \file events.h
 * \brief Programme déclarant les fonctions utilisées pour gérer les événements
 * \author IOPETI Hugo
 * \author YVOZ Ludovic
 * \date 16 Novembre 2020
 */
 
#ifndef handle_events
#include "database.h"
#include <math.h>

/**
 * \brief La fonction gère les évènements ayant eu lieu et qui n'ont pas encore été traités
 * \param event paramètre qui contient les événements
 * \param world les données du monde
 */
void handle_events(SDL_Event *event,world_t *world);


/**
 * \brief La fonction gère les évènements ayant eu lieu pendant une pause et qui n'ont pas encore été traités
 * \param event paramètre qui contient les événements
 * \param world les données du monde
 */
void handle_pause_events(SDL_Event *event,world_t *world);


/**
 * \brief La fonction gère les évènements ayant lieu lorsque la partie est finie et qui n'ont pas encore été traités
 * \param event paramètre qui contient les événements
 * \param world les données du monde
 */
void handle_end_events(SDL_Event *event,world_t *world);

#endif