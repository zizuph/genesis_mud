// /d/Genesis/start/human/town/tfloor2.c

/* 
 *  This is the second floor in the tower of realms
 * 
 *  Coded by Maniac 20/12/96
 */ 

#include "tower.h"
#include "../defs.h"

inherit TOWER_FLOOR;

void
create_tower_floor()
{
     set_short("Tower of Realms Floor Two"); 
     set_long("This is the second floor of the Tower of Realms. " +
              FLOOR_MAINDESC + FLOOR_STAIRDESC + "\n");
     set_floor_number(2); 

     ADD_FLOOR_ITEMS;
     add_exit(TOWN_DIR + "tfloor1", "down", 0); 
     add_exit(TOWN_DIR + "tfloor3", "up", 0); 
}

