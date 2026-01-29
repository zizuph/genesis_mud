/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/sea/std/sector_1_1_2_room";

#include "barracuda.h"

void
create_water_room()
{
    make_the_room("\n", 15, 9, 2);

    add_swim_exit(SECTOR_PATH(15,8,2)+"wr_15_8_2", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(15,10,2)+"wr_15_10_2", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(14,9,2)+"wr_14_9_2", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(14,8,2)+"wr_14_8_2", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(14,10,2)+"wr_14_10_2", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(15,9,1)+"wr_15_9_1", "up", 0, 0);
    add_swim_exit(SECTOR_PATH(15,9,3)+"wr_15_9_3", "down", 0, 2);
    reset_room();
}
