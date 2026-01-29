// /d/Genesis/start/human/town/tfloor4.c

/* 
 *  This is the fourth floor in the tower of realms
 * 
 *  Coded by Maniac 20/12/96
 */ 

#include "tower.h"
#include "../defs.h"

inherit TOWER_FLOOR;

void
create_tower_floor()
{
     set_short("Tower of Realms Floor Four"); 
     set_long("This is the fourth floor of the Tower of Realms. " +
              FLOOR_MAINDESC + "\n");
     set_floor_number(4); 
     ADD_FLOOR_ITEMS;

     add_exit(TOWN_DIR + "tfloor3", "down", 0); 
     // add_exit(TOWN_DIR + "tfloor5", "up", 0); 
}

