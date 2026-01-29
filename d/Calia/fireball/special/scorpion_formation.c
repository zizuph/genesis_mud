
/* 
    ~Calia/fireball/special/scorpion_formation.c 

    Support for the scorpion formation in fireball. This is
    a fairly defensive formation. 

    Coded by Maniac@Genesis, July 1999

    Copyright (C) Miguel Leith 1999
*/ 

#pragma strict_types
#pragma no_inherit

#include "defs.h"
#include FIREBALL_HEADER
#include <std.h>

inherit FIREBALL_NPC_CONTROL; 

/*

      1   2   3   4   5   6   7   8   9  10  11

11                  |   |   |   |                  11
10              |   |   |   |   |   |              10
 9          |   |   |   |   |   |   |   |           9
 8      |   |   |   |   |   |   |   |   |   |       8
 7  |   |   |   |   |   |###|   |   |   |   |   |   7
 6  |   |   |   |   |###|###|###|   |   |   |   |   6
 5  |   |   |   |   |   |###|   |   |   |   |   |   5
 4      |   |   |   |   |   |   |   |   |   |       4
 3          |   |   |   |   |   |   |   |           3
 2              |   |   |   |   |   |               2
 1                  |   |   |   |                   1

      1   2   3   4   5   6   7   8   9  10  11     

 */ 

void
create_team_manager()
{
    mapping scorpion_attack_north, scorpion_attack_south, 
            scorpion_defense_north, scorpion_defense_south; 
    string *ix; 
    int i; 

    scorpion_defense_north = 
         ([ 

           FIREBALL_NORTH_GOAL       :   ({ 6,2, 5,10, 7,10, 6,4 }),  
           FIREBALL_NORTHWEST_FIELD  :   ({ 5,2, 3,9, 6,8, 5,3 }),  
           FIREBALL_NORTH_FIELD      :   ({ 6,2, 5,9, 7,9, 6,3 }), 
           FIREBALL_NORTHEAST_FIELD  :   ({ 7,2, 6,8, 9,9, 7,3 }), 
           FIREBALL_WEST_POINT       :   ({ 6,1, 1,6, 7,8, 5,3 }), 
           FIREBALL_WEST_FIELD       :   ({ 6,1, 3,6, 7,8, 5,3 }),  
           FIREBALL_MID_FIELD        :   ({ 6,1, 4,6, 8,6, 6,3 }),  
           FIREBALL_EAST_FIELD       :   ({ 6,1, 5,8, 9,6, 7,3 }),  
           FIREBALL_EAST_POINT       :   ({ 6,1, 5,8, 11,6, 7,3 }),  
           FIREBALL_SOUTHWEST_FIELD  :   ({ 6,1, 3,3, 8,5, 5,2 }),  
           FIREBALL_SOUTH_FIELD      :   ({ 6,1, 3,4, 9,4, 6,3 }),  
           FIREBALL_SOUTHEAST_FIELD  :   ({ 6,1, 4,5, 9,3, 7,2 }),  
           FIREBALL_SOUTH_GOAL       :   ({ 6,1, 3,3, 9,3, 6,2 })

         ]); 

    ix = m_indexes(scorpion_defense_north); 
    scorpion_defense_south = ([ ]); 
    for (i = 0; i < sizeof(ix); i++) {
        scorpion_defense_south += 
            ([ reflect_sector(ix[i]) : 
               reflect_coords(scorpion_defense_north[ix[i]])
            ]); 
    } 
    set_formation_defense_north(scorpion_defense_north); 
    set_formation_defense_south(scorpion_defense_south); 

    scorpion_attack_north = 
         ([ 

           FIREBALL_NORTH_GOAL       :   ({ 6,2, 5,11, 7,11, 6,4 }),  
           FIREBALL_NORTHWEST_FIELD  :   ({ 5,2, 4,9, 6,11, 5,3 }),  
           FIREBALL_NORTH_FIELD      :   ({ 6,2, 5,10, 7,10, 6,3 }), 
           FIREBALL_NORTHEAST_FIELD  :   ({ 7,2, 6,11, 8,9, 7,3 }), 
           FIREBALL_WEST_POINT       :   ({ 6,1, 2,8, 6,9, 5,3 }), 
           FIREBALL_WEST_FIELD       :   ({ 6,1, 3,8, 6,9, 5,3 }),  
           FIREBALL_MID_FIELD        :   ({ 6,1, 4,9, 8,9, 6,3 }),  
           FIREBALL_EAST_FIELD       :   ({ 6,1, 6,9, 9,8, 7,3 }),  
           FIREBALL_EAST_POINT       :   ({ 6,1, 6,9, 10,8, 7,3 }),  
           FIREBALL_SOUTHWEST_FIELD  :   ({ 6,1, 3,6, 7,8, 6,3 }),  
           FIREBALL_SOUTH_FIELD      :   ({ 6,1, 3,6, 9,6, 6,3 }),  
           FIREBALL_SOUTHEAST_FIELD  :   ({ 6,1, 5,8, 9,6, 6,3 }),  
           FIREBALL_SOUTH_GOAL       :   ({ 6,1, 3,5, 9,5, 6,3 })

         ]); 

    scorpion_attack_south = ([ ]); 
    for (i = 0; i < sizeof(ix); i++) {
        scorpion_attack_south += 
            ([ reflect_sector(ix[i]) : 
               reflect_coords(scorpion_attack_north[ix[i]])
            ]); 
    } 
    set_formation_attack_north(scorpion_attack_north); 
    set_formation_attack_south(scorpion_attack_south); 
}

string
query_name() 
{
    return "scorpion"; 
}
