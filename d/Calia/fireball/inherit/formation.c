
/* 
    ~Calia/fireball/special/formation.c 

    This code contains support for the formation mappings for 
    fireball npc teams. A formation mapping describes the position
    each team member should be in the arena when the ball is in the
    designated sector. Attacking means the team has the ball, 
    otherwise it's defending. Abstracted from the game handler to
    offer more modularity and allow more formations than the original
    one (arrow). 

    Coded by Maniac@Genesis, July 1999

    Copyright (C) Miguel Leith 1999
*/ 

#pragma strict_types

#include "defs.h"
#include FIREBALL_HEADER
#include <std.h>

mapping attack_north, attack_south, defense_north, defense_south; 


/* Reflect a Firedrome arena sector in the horizontal axis and
   vertical axis */ 
string
reflect_sector(string sector)
{
    switch (sector) {
        case FIREBALL_NORTH_GOAL : 
            return FIREBALL_SOUTH_GOAL; 
            break; 
        case FIREBALL_SOUTH_GOAL : 
            return FIREBALL_NORTH_GOAL; 
            break; 
        case FIREBALL_NORTH_FIELD : 
            return FIREBALL_SOUTH_FIELD; 
            break; 
        case FIREBALL_SOUTH_FIELD : 
            return FIREBALL_NORTH_FIELD; 
            break; 
        case FIREBALL_WEST_FIELD : 
            return FIREBALL_EAST_FIELD; 
            break; 
        case FIREBALL_EAST_FIELD : 
            return FIREBALL_WEST_FIELD; 
            break; 
        case FIREBALL_WEST_POINT : 
            return FIREBALL_EAST_POINT; 
            break; 
        case FIREBALL_EAST_POINT : 
            return FIREBALL_WEST_POINT; 
            break; 
        case FIREBALL_NORTHWEST_FIELD : 
            return FIREBALL_SOUTHEAST_FIELD; 
            break; 
        case FIREBALL_NORTHEAST_FIELD : 
            return FIREBALL_SOUTHWEST_FIELD; 
            break; 
        case FIREBALL_SOUTHWEST_FIELD : 
            return FIREBALL_NORTHEAST_FIELD; 
            break; 
        case FIREBALL_SOUTHEAST_FIELD : 
            return FIREBALL_NORTHWEST_FIELD; 
            break; 
        default : 
            return sector; 
            break; 
    } 
}




/* 
 * Function:     reflect_coords
 * Description:  Reflects a group of four coordinates (represented
 *               as an array of eight integers) corresponding 
 *               to the positions of four team players (defender, 
 *               left midfielder, right midfielder, attacker). This 
 *               is used to convert a set of positions for a team 
 *               kicking south to one kicking north, or vice versa. 
 */
int *
reflect_coords(int *coords)
{
    coords = secure_var(coords); 
    coords[0] = 12 - coords[0];  
    coords[1] = 12 - coords[1]; 
    coords[2] = 12 - coords[2]; 
    coords[3] = 12 - coords[3]; 
    coords[4] = 12 - coords[4]; 
    coords[5] = 12 - coords[5]; 
    coords[6] = 12 - coords[6];
    coords[7] = 12 - coords[7];     
    return coords; 
}


mapping
query_formation(int attacking, int kicking) 
{
    if (attacking) {
        if (kicking == FIREBALL_KICKING_NORTH)
            return attack_north; 
        else
            return attack_south; 
    } 
    else {
        if (kicking == FIREBALL_KICKING_NORTH)
            return defense_north; 
        else
            return defense_south; 
    } 
}


/* Set the formation mapping for when a team kicking north
   is attacking */ 
void
set_formation_attack_north(mapping m)
{
    attack_north = m; 
}


/* Set the formation mapping for when a team kicking south
   is attacking */ 
void
set_formation_attack_south(mapping m)
{
    attack_south = m; 
}


/* Set the formation mapping for when a team kicking north
   is defending. */ 
void
set_formation_defense_north(mapping m)
{
    defense_north = m; 
}


/* Set the formation mapping for when a team kicking south
   is defending. */ 
void
set_formation_defense_south(mapping m)
{
    defense_south = m; 
}
