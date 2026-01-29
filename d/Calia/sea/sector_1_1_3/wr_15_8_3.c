/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/sea/std/sector_1_1_3_room";

void
create_water_room()
{
    make_the_room("\n", 15, 8, 3);

    add_swim_exit(SECTOR_PATH(15,7,3)+"wr_15_7_3", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(15,9,3)+"wr_15_9_3", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(14,8,3)+"wr_14_8_3", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(14,7,3)+"wr_14_7_3", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(14,9,3)+"wr_14_9_3", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(15,8,2)+"wr_15_8_2", "up", 0, 0);
    add_swim_exit(SECTOR_PATH(15,8,4)+"wr_15_8_4", "down", 0, 2);
}
