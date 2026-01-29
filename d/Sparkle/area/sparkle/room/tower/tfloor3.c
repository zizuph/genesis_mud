// /d/Genesis/start/human/town/tfloor3.c

/*
 *  This is the third floor in the tower of realms
 *
 *  Coded by Maniac 20/12/96
 */

#include "defs.h"

inherit TOWER_FLOOR;

void
create_tower_floor()
{
     set_short("Tower of Realms Floor Three");
     set_long("This is the third floor of the Tower of Realms. " +
              FLOOR_MAINDESC + FLOOR_STAIRDESC + "\n");
     set_floor_number(3);
     ADD_FLOOR_ITEMS;

     add_exit("tfloor2", "down", 0);
     add_exit("tfloor4", "up", 0);
}

