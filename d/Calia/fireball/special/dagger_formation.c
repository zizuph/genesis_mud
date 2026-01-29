
/* 
    ~Calia/fireball/special/dagger_formation.c 

    Support for the dagger formation in fireball. This is
    a very defensive formation. 

    Coded by Maniac@Genesis, July 1999

    Copyright (C) Miguel Leith 1999
*/ 

#pragma strict_types
#pragma no_inherit

#include "defs.h"
#include FIREBALL_HEADER
#include <std.h>

inherit FIREBALL_NPC_CONTROL; 

mapping dagger_defense_north, dagger_defense_south, 
        dagger_attack_north, dagger_attack_south; 



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
    string *ix; 
    int i; 


                              /*  DAGGER FORMATION  */ 

    dagger_defense_north = 
         ([ 

           FIREBALL_NORTH_GOAL       :   ({ 6,1, 4,6, 8,6, 6,10 }),  
           FIREBALL_NORTHWEST_FIELD  :   ({ 5,1, 3,6, 6,3, 3,9 }),  
           FIREBALL_NORTH_FIELD      :   ({ 6,1, 4,5, 8,5, 6,9 }), 
           FIREBALL_NORTHEAST_FIELD  :   ({ 7,1, 6,3, 9,6, 9,9 }), 
           FIREBALL_WEST_POINT       :   ({ 6,1, 1,6, 6,3, 4,8 }), 
           FIREBALL_WEST_FIELD       :   ({ 6,1, 3,6, 6,3, 5,8 }),  
           FIREBALL_MID_FIELD        :   ({ 6,1, 5,4, 7,4, 6,8 }),  
           FIREBALL_EAST_FIELD       :   ({ 6,1, 6,3, 9,6, 7,8 }),  
           FIREBALL_EAST_POINT       :   ({ 6,1, 6,3, 11,6, 8,8 }),  
           FIREBALL_SOUTHWEST_FIELD  :   ({ 6,1, 3,3, 6,2, 4,6 }),  
           FIREBALL_SOUTH_FIELD      :   ({ 6,1, 6,2, 6,3, 6,8 }),  
           FIREBALL_SOUTHEAST_FIELD  :   ({ 6,1, 6,2, 9,3, 8,6 }),  
           FIREBALL_SOUTH_GOAL       :   ({ 6,1, 5,2, 7,2, 6,8 })
         
         ]); 

    ix = m_indexes(dagger_defense_north); 
    dagger_defense_south = ([ ]); 
    for (i = 0; i < sizeof(ix); i++) {
        dagger_defense_south += 
            ([ reflect_sector(ix[i]) : 
               reflect_coords(dagger_defense_north[ix[i]])
            ]); 
    } 
    set_formation_defense_north(dagger_defense_north); 
    set_formation_defense_south(dagger_defense_south); 

    dagger_attack_north = 
         ([ 

           FIREBALL_NORTH_GOAL       :   ({ 6,2, 5,8, 7,8, 6,11 }), 
           FIREBALL_NORTHWEST_FIELD  :   ({ 5,2, 3,6, 7,4, 3,9 }), 
           FIREBALL_NORTH_FIELD      :   ({ 6,2, 4,6, 8,6, 6,9 }), 
           FIREBALL_NORTHEAST_FIELD  :   ({ 7,2, 5,4, 9,6, 9,9 }), 
           FIREBALL_WEST_POINT       :   ({ 5,2, 1,6, 6,3, 4,8 }), 
           FIREBALL_WEST_FIELD       :   ({ 5,2, 3,6, 6,3, 5,9 }),
           FIREBALL_MID_FIELD        :   ({ 6,1, 4,6, 8,6, 6,8 }), 
           FIREBALL_EAST_FIELD       :   ({ 7,2, 6,3, 9,6, 7,9}),
           FIREBALL_EAST_POINT       :   ({ 7,2, 6,3, 11,6, 8,8 }), 
           FIREBALL_SOUTHWEST_FIELD  :   ({ 6,1, 3,4, 6,3, 4,7 }), 
           FIREBALL_SOUTH_FIELD      :   ({ 6,1, 5,4, 7,4, 6,8 }), 
           FIREBALL_SOUTHEAST_FIELD  :   ({ 6,1, 6,3, 9,4, 8,7 }), 
           FIREBALL_SOUTH_GOAL       :   ({ 6,1, 5,3, 7,3, 6,8 })

         ]); 

    dagger_attack_south = ([ ]); 
    for (i = 0; i < sizeof(ix); i++) {
        dagger_attack_south += 
            ([ reflect_sector(ix[i]) : 
               reflect_coords(dagger_attack_north[ix[i]])
            ]); 
    } 
    set_formation_attack_north(dagger_attack_north); 
    set_formation_attack_south(dagger_attack_south); 
}

string
query_name() 
{
    return "dagger"; 
}
