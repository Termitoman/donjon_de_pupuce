/**
 * \file graphique.c
 * \brief Programme définissant les fonctions déclarées dans graphique.h
 * \author YVOZ Ludovic
 * \author IOPETI Hugo
 * \date 30 avril 2020
 */

#include "graphique.h"

void apply_sprite(SDL_Renderer *renderer, SDL_Texture *texture, sprite_t *sprite)
{
    if (sprite->is_visible == 0)
    {
        SDL_Rect SrcR; //On donne les coordonnées de l'image que l'on veut utiliser sur la sprite cheet
        SrcR.w = sprite->w[sprite->wich_img[0]];
        SrcR.h = sprite->h;

        SrcR.x = 0;
        for (int i = 0; i < sprite->wich_img[0]; i++)
        { //On donne la coordonnée x du sprite sur la sprite sheet alors que la largeur entre chaque colonne est différente
            SrcR.x += sprite->w[i] + SPACE_BETWEEN_COLUMNS;
        }

        SrcR.y = sprite->wich_img[1] * (SPACE_BETWEEN_ROWS + sprite->h);

        apply_image(texture, renderer, SrcR, sprite->x - sprite->w[sprite->wich_img[0]] / 2, sprite->y - sprite->h / 2); //On donne les coordonnées du coin en haut à gauche du sprite à partir du centre du sprite
    }
}

void init_resources(SDL_Renderer *renderer, resources_t *resources)
{
    resources->player = load_transparent_image("ressources/player/sprite_sheet.bmp", renderer, 230, 80, 235);
    resources->player_attack_hori = load_transparent_image("ressources/player/atk_hori_sprite_sheet.bmp", renderer, 230, 80, 235);
    resources->player_attack_verti = load_transparent_image("ressources/player/atk_verti_sprite_sheet.bmp", renderer, 230, 80, 235);
    resources->slime = load_transparent_image("ressources/monsters/slime.bmp", renderer, 230, 80, 235);
    resources->vertical_skull = load_transparent_image("ressources/monsters/vertical_skull.bmp", renderer, 230, 80, 235);
    resources->skull_turret = load_transparent_image("ressources/monsters/skull_turret.bmp", renderer, 230, 80, 235);
    resources->skull_projectile = load_transparent_image("ressources/monsters/skull_projectile.bmp", renderer, 230, 80, 235);
    resources->boss = load_transparent_image("ressources/boss/boss_sprite_sheet.bmp", renderer, 230, 80, 235);
    resources->boss_atk = load_transparent_image("ressources/boss/boss_atk_sprite_sheet.bmp", renderer, 230, 80, 235);

    //On s'occupe des textures de la salle
    resources->room = malloc(sizeof(room_resources_t));
    resources->room->background = load_image("ressources/map/background1.bmp", renderer);
    resources->room->door_down_close = load_image("ressources/map/door_down_close.bmp", renderer);
    resources->room->door_up_close = load_image("ressources/map/door_up_close.bmp", renderer);
    resources->room->door_right_close = load_image("ressources/map/door_right_close.bmp", renderer);
    resources->room->door_left_close = load_image("ressources/map/door_left_close.bmp", renderer);
    resources->room->door_down_open = load_image("ressources/map/door_down_open.bmp", renderer);
    resources->room->door_up_open = load_image("ressources/map/door_up_open.bmp", renderer);
    resources->room->door_right_open = load_image("ressources/map/door_right_open.bmp", renderer);
    resources->room->door_left_open = load_image("ressources/map/door_left_open.bmp", renderer);
    resources->room->wall_down = load_image("ressources/map/wall_down.bmp", renderer);
    resources->room->wall_up = load_image("ressources/map/wall_up.bmp", renderer);
    resources->room->wall_right = load_image("ressources/map/wall_right.bmp", renderer);
    resources->room->wall_left = load_image("ressources/map/wall_left.bmp", renderer);

    //On s'occupe de la police d'écriture
    resources->font = load_font("ressources/font/pixel_font.ttf", 18);
    resources->smaller_font = load_font("ressources/font/pixel_font.ttf", 12);
    resources->color.a = 0;
    resources->color.r = 250;
    resources->color.b = 250;
    resources->color.g = 250;

    //On s'occupe des affichages supplémentaires
    resources->add_disp = malloc(sizeof(add_disp_t));
    resources->add_disp->pause_screen = load_transparent_image("ressources/additional_displays/pause_screen.bmp", renderer, 230, 80, 235);
    resources->add_disp->black_background = load_image("ressources/additional_displays/black_background.bmp", renderer);
    resources->add_disp->death_screen = load_image("ressources/additional_displays/death_screen.bmp", renderer);
    resources->add_disp->rules = load_image("ressources/additional_displays/rules.bmp", renderer);
    resources->add_disp->end_screen = load_image("ressources/additional_displays/end_screen.bmp", renderer);
    resources->add_disp->welcome_screen = load_image("ressources/additional_displays/welcome_screen.bmp", renderer);
    resources->add_disp->waiting_screen_1 = load_image("ressources/additional_displays/waiting_screen_1.bmp", renderer);
    resources->add_disp->waiting_screen_2 = load_image("ressources/additional_displays/waiting_screen_2.bmp", renderer);
    resources->add_disp->waiting_screen_3 = load_image("ressources/additional_displays/waiting_screen_3.bmp", renderer);
}

void clean_resources(resources_t *resources)
{
    clean_image(resources->player);
    clean_image(resources->player_attack_hori);
    clean_image(resources->player_attack_verti);
    clean_image(resources->slime);
    clean_image(resources->vertical_skull);
    clean_image(resources->skull_turret);
    clean_image(resources->skull_projectile);
    clean_image(resources->boss);
    clean_image(resources->boss_atk);

    //On s'occupe des textures de la salle
    clean_image(resources->room->background);
    clean_image(resources->room->door_down_close);
    clean_image(resources->room->door_up_close);
    clean_image(resources->room->door_right_close);
    clean_image(resources->room->door_left_close);
    clean_image(resources->room->door_down_open);
    clean_image(resources->room->door_up_open);
    clean_image(resources->room->door_right_open);
    clean_image(resources->room->door_left_open);
    clean_image(resources->room->wall_down);
    clean_image(resources->room->wall_up);
    clean_image(resources->room->wall_right);
    clean_image(resources->room->wall_left);
    free(resources->room);

    //On s'occupe de la police d'écriture
    clean_font(resources->font);

    //On s'occupe des affichages supplémentaires
    clean_image(resources->add_disp->pause_screen);
    clean_image(resources->add_disp->black_background);
    clean_image(resources->add_disp->death_screen);
    clean_image(resources->add_disp->rules);
    clean_image(resources->add_disp->end_screen);
    clean_image(resources->add_disp->welcome_screen);
    clean_image(resources->add_disp->waiting_screen_1);
    clean_image(resources->add_disp->waiting_screen_2);
    clean_image(resources->add_disp->waiting_screen_3);
    free(resources->add_disp);
}

void apply_background(SDL_Renderer *renderer, resources_t *resources)
{
    if (resources->room->background != NULL)
    {
        SDL_Rect SrcR = {0, 0, 0, 0};
        SDL_QueryTexture(resources->room->background, NULL, NULL, &SrcR.w, &SrcR.h); //On demande directement les dimensions du background
        apply_image(resources->room->background, renderer, SrcR, 0, 0);
    }
}

void apply_part_of_background(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y)
{
    SDL_Rect SrcR = {0, 0, 0, 0};
    SDL_QueryTexture(texture, NULL, NULL, &SrcR.w, &SrcR.h); //On demande directement les dimensions de l'image à afficher
    apply_image(texture, renderer, SrcR, x, y);
}

void refresh_graphics(SDL_Renderer *renderer, world_t *world, resources_t *resources)
{
    //on vide le renderer
    SDL_RenderClear(renderer);

    //application des ressources dans le renderer
    //On gère l'affichage de la salle
    apply_background(renderer, resources);
    refresh_room(renderer, world, resources);
    //On gère l'affichage des sprites
    apply_sprite(renderer, resources->player, world->player->sprite);
    if (world->floor->type == 0)
    {
        apply_monsters(renderer, world, resources);
        apply_missiles(renderer, world, resources);
    }
    else
    {
        apply_sprite(renderer, resources->boss, world->boss->sprite);
        apply_sprite(renderer, resources->boss_atk, world->boss->atk_sprite);
    }
    apply_sprite(renderer, resources->player_attack_hori, world->player->atk_sprite_hori);
    apply_sprite(renderer, resources->player_attack_verti, world->player->atk_sprite_verti);

    //On gère l'affichage des textes
    //Affichage des points de vie
    char player_hp_string[10];
    sprintf(player_hp_string, "HP = %d", world->player->hp);
    apply_text(renderer, resources->font, resources->color, player_hp_string, 10, 50);

    if (world->floor->type == 1)
    {
        char boss_hp_string[10];
        sprintf(boss_hp_string, "HP = %d", world->boss->hp);
        apply_text(renderer, resources->font, resources->color, boss_hp_string, SCREEN_WIDTH - 100, 50);
    }

    //On gère l'affichage d'un message pour passer d'une salle à l'autre
    if (sprite_is_out_of_additional_bounds(world->player->sprite, world->floor->direction, world->room_state) == 1)
    {
        if (world->floor->type == 0)
        {
            apply_text(renderer, resources->smaller_font, resources->color, "Appuyez sur la barre espace pour changer de salle !", SCREEN_WIDTH / 2 - 190, SCREEN_HEIGHT / 2 - 12);
        }
        else
        {
            if (world->wants_reward == 1)
            {
                apply_text(renderer, resources->smaller_font, resources->color, "Bravo, vous avez reussi a vous echapper !", SCREEN_WIDTH / 2 - 160, SCREEN_HEIGHT / 2 - 24);
                apply_text(renderer, resources->smaller_font, resources->color, "Appuyez sur espace pour reclamer vos recompenses !", SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2 + 12);
            }
            else
            {
                reward_message(world, renderer, resources);
            }
        }
    }

    // on met à jour l'écran
    SDL_RenderPresent(renderer);
}

void refresh_room(SDL_Renderer *renderer, world_t *world, resources_t *resources)
{
    switch (world->floor->direction)
    {

    case 0:
        if (world->room_state != 1)
        { //Si le combat est terminé, la porte est ouverte
            apply_part_of_background(renderer, resources->room->door_down_open, PLAY_ZONE_ADD_TOP_X + 1, PLAY_ZONE_BOTTOM_WALL - 1);
        }
        else
        { //Sinon, elle est fermée
            apply_part_of_background(renderer, resources->room->door_down_close, PLAY_ZONE_ADD_TOP_X + 1, PLAY_ZONE_BOTTOM_WALL - 1);
        }
        apply_part_of_background(renderer, resources->room->wall_up, PLAY_ZONE_ADD_TOP_X, 0);
        apply_part_of_background(renderer, resources->room->wall_right, PLAY_ZONE_RIGHT_WALL, PLAY_ZONE_ADD_LEFT_Y + 1);
        apply_part_of_background(renderer, resources->room->wall_left, 0, PLAY_ZONE_ADD_LEFT_Y);
        break;

    case 1:
        if (world->room_state != 1)
        {
            apply_part_of_background(renderer, resources->room->door_right_open, PLAY_ZONE_RIGHT_WALL, PLAY_ZONE_ADD_LEFT_Y + 1);
        }
        else
        {
            apply_part_of_background(renderer, resources->room->door_right_close, PLAY_ZONE_RIGHT_WALL, PLAY_ZONE_ADD_LEFT_Y + 1);
        }
        apply_part_of_background(renderer, resources->room->wall_up, PLAY_ZONE_ADD_TOP_X, 0);
        apply_part_of_background(renderer, resources->room->wall_down, PLAY_ZONE_ADD_TOP_X + 1, PLAY_ZONE_BOTTOM_WALL - 1);
        apply_part_of_background(renderer, resources->room->wall_left, 0, PLAY_ZONE_ADD_LEFT_Y);
        break;

    case 2:
        if (world->room_state != 1)
        {
            apply_part_of_background(renderer, resources->room->door_left_open, 0, PLAY_ZONE_ADD_LEFT_Y);
        }
        else
        {
            apply_part_of_background(renderer, resources->room->door_left_close, 0, PLAY_ZONE_ADD_LEFT_Y);
        }
        apply_part_of_background(renderer, resources->room->wall_up, PLAY_ZONE_ADD_TOP_X, 0);
        apply_part_of_background(renderer, resources->room->wall_right, PLAY_ZONE_RIGHT_WALL, PLAY_ZONE_ADD_LEFT_Y + 1);
        apply_part_of_background(renderer, resources->room->wall_down, PLAY_ZONE_ADD_TOP_X + 1, PLAY_ZONE_BOTTOM_WALL - 1);
        break;

    case 3:
        if (world->room_state != 1)
        {
            apply_part_of_background(renderer, resources->room->door_up_open, PLAY_ZONE_ADD_TOP_X, 0);
        }
        else
        {
            apply_part_of_background(renderer, resources->room->door_up_close, PLAY_ZONE_ADD_TOP_X, 0);
        }
        apply_part_of_background(renderer, resources->room->wall_down, PLAY_ZONE_ADD_TOP_X + 1, PLAY_ZONE_BOTTOM_WALL - 1);
        apply_part_of_background(renderer, resources->room->wall_right, PLAY_ZONE_RIGHT_WALL, PLAY_ZONE_ADD_LEFT_Y + 1);
        apply_part_of_background(renderer, resources->room->wall_left, 0, PLAY_ZONE_ADD_LEFT_Y);
        break;
        default:
        break;
    }
}

void apply_monsters(SDL_Renderer *renderer, world_t *world, resources_t *resources)
{
    //applications des monstres dans le renderer
    for (int i = 0; i < world->nb_enemies; i++)
    {
        switch (world->enemies[i]->type)
        {
        case 1:
            apply_sprite(renderer, resources->slime, world->enemies[i]->sprite);
            break;

        case 2:
            apply_sprite(renderer, resources->vertical_skull, world->enemies[i]->sprite);
            break;

        case 3:
            apply_sprite(renderer, resources->skull_turret, world->enemies[i]->sprite);
            break;
            default:
            break;
        }
    }
}

void apply_missiles(SDL_Renderer *renderer, world_t *world, resources_t *resources)
{
    for (int i = 0; i < world->nb_missiles; i++)
    {
        apply_sprite(renderer, resources->skull_projectile, world->missiles[i]->sprite);
    }
}

void apply_text(SDL_Renderer *renderer, TTF_Font *font, SDL_Color color, char *string, int x, int y)
{
    SDL_Texture *texture = load_text(string, renderer, font, color);
    SDL_Rect rect = {0, 0, 0, 0};
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
    apply_image(texture, renderer, rect, x, y);
}

void reward_message(world_t *world, SDL_Renderer *renderer, resources_t *resources)
{
    //On change le fond d'écran
    SDL_RenderClear(renderer);
    apply_part_of_background(renderer, resources->add_disp->black_background, 0, 0);

    //On fait apparaître les textes de fin
    apply_text(renderer, resources->font, resources->color, "Vous pouvez ameliorer une de vos statistiques !", SCREEN_WIDTH / 2 - 280, SCREEN_HEIGHT / 4 - 42);

    //On s'occupe du bonus d'hp
    if (world->player->bonus_hp < 50)
    { //On pose une limite aux hp bonus
        char player_bonus_hp_string[100];
        sprintf(player_bonus_hp_string, "Bonus hp = %d, amelioration : %d + 5 | bouton K", world->player->bonus_hp, world->player->bonus_hp);
        apply_text(renderer, resources->font, resources->color, player_bonus_hp_string, SCREEN_WIDTH / 2 - 280, SCREEN_HEIGHT / 3 - 12);
    }
    else
    {
        apply_text(renderer, resources->font, resources->color, "Vous avez deja le maximum d'hp bonus possible !", SCREEN_WIDTH / 2 - 280, SCREEN_HEIGHT / 3 - 12);
    }

    //On s'occupe du bonus d'attaque
    if (world->player->bonus_atk_power < 50)
    { //On pose une limite à l'attaque bonus
        char player_bonus_atk_string[100];
        sprintf(player_bonus_atk_string, "Bonus atk power = %d, amelioration : %d + 5 | bouton L", world->player->bonus_atk_power, world->player->bonus_atk_power);
        apply_text(renderer, resources->font, resources->color, player_bonus_atk_string, SCREEN_WIDTH / 2 - 280, SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 20 - 12);
    }
    else
    {
        apply_text(renderer, resources->font, resources->color, "Vous avez deja le maximum d'attaque bonus possible !", SCREEN_WIDTH / 2 - 280, SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 20 - 12);
    }

    //On s'occupe du bonus de vitesse d'attaque
    if (world->player->bonus_atk_speed < 20)
    { //On pose une limite à la vitesse d'attaque bonus
        char player_bonus_spd_string[100];
        sprintf(player_bonus_spd_string, "Bonus atk speed = %d, amelioration : %d + 2 | bouton M", world->player->bonus_atk_speed, world->player->bonus_atk_speed);
        apply_text(renderer, resources->font, resources->color, player_bonus_spd_string, SCREEN_WIDTH / 2 - 280, SCREEN_HEIGHT / 2 + SCREEN_HEIGHT / 14 - 12);
    }
    else
    {
        apply_text(renderer, resources->font, resources->color, "Vous avez atteint la vitesse d'attaque bonus maximale !", SCREEN_WIDTH / 2 - 280, SCREEN_HEIGHT / 2 + SCREEN_HEIGHT / 12 - 12);
    }

    //On affiche les instructions
    apply_text(renderer, resources->smaller_font, resources->color, "Pour prendre votre recompense, appuyez sur la touche correspondante.", SCREEN_WIDTH / 2 - 280, (SCREEN_HEIGHT / 2) + 74);
    apply_text(renderer, resources->smaller_font, resources->color, "Attention, vous n'avez le droit qu'a un seul bonus, reflechissez bien !", SCREEN_WIDTH / 2 - 240, (SCREEN_HEIGHT / 3) * 2 + 72);
    apply_text(renderer, resources->smaller_font, resources->color, "(Pour quitter, faites la croix)", SCREEN_WIDTH / 2 - 100, (SCREEN_HEIGHT / 3) * 2 + 108);
}

void end_screen(world_t *world, SDL_Renderer *renderer, resources_t *resources)
{
    if (world->player->hp <= 0)
    { //Si le joueur est mort
        apply_part_of_background(renderer, resources->add_disp->death_screen, 0, 0);
    }
    else
    {
        apply_part_of_background(renderer, resources->add_disp->end_screen, 0, 0);
    }
    SDL_RenderPresent(renderer);
    world->play_again = 2;
}

void pause_screen(world_t *world, SDL_Renderer *renderer, resources_t *resources)
{
    apply_part_of_background(renderer, resources->add_disp->pause_screen, 0, 0);
    SDL_RenderPresent(renderer);
}

void start_screen(SDL_Renderer *renderer, resources_t *resources)
{
    apply_part_of_background(renderer, resources->add_disp->welcome_screen, 0, 0);
    SDL_RenderPresent(renderer);
    SDL_Delay(4000);
    apply_part_of_background(renderer, resources->add_disp->rules, 0, 0);
    SDL_RenderPresent(renderer);
    SDL_Delay(8000);
    apply_part_of_background(renderer, resources->add_disp->waiting_screen_1, 0, 0);
    SDL_RenderPresent(renderer);
    SDL_Delay(1000);
    apply_part_of_background(renderer, resources->add_disp->waiting_screen_2, 0, 0);
    SDL_RenderPresent(renderer);
    SDL_Delay(1000);
    apply_part_of_background(renderer, resources->add_disp->waiting_screen_3, 0, 0);
    SDL_RenderPresent(renderer);
    SDL_Delay(1000);
}
