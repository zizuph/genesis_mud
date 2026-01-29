// /d/Genesis/start/human/town/tower_floor.c 

/* 
   This should be inherited by all floors of the tower of realms.
   It sets up the correct exits on creation. 
   Use the create function: create_tower_floor(), 
   and be sure to call set_floor_number(n) in this function 
   if you want the exits to show up!

   Coded by Maniac, 20/12/96 
*/ 

#pragma save_binary
#pragma strict_types

#include "defs.h"
#include <stdproperties.h>

inherit "/std/room";

int floor_number;


void
set_floor_number(int n)
{
    floor_number = n;
}

int
query_floor_number()
{
    return floor_number;
}


void
setup_floor_exits()
{
     int i;
     string *ex;  

     ex = FLOOR_EXITS(query_floor_number()); 

     for (i = 0; i < sizeof(ex); i += 3)  
         if (member_array(ex[i+1], query_exit_cmds()) == -1) 
             add_exit(ex[i], ex[i+1], ex[i+2]); 
}


void
create_tower_floor()
{
}

void
create_room()
{
    add_prop(ROOM_I_INSIDE, 1); 
    create_tower_floor();  
    setup_floor_exits(); 
}

