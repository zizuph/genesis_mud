/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/sea/std/sector_1_1_0_room";

void
create_water_room()
{
    make_the_room("\n", 15, 9, 0);

    add_swim_exit(SECTOR_PATH(15,8,0)+"wr_15_8_0", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(15,10,0)+"wr_15_10_0", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(14,9,0)+"wr_14_9_0", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(14,8,0)+"wr_14_8_0", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(14,10,0)+"wr_14_10_0", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(15,9,1)+"wr_15_9_1", "down", 0, 2);
    add_row_exit(SECTOR_PATH(15,8,0)+"wr_15_8_0", "north", 0, 1);
    add_row_exit(SECTOR_PATH(15,10,0)+"wr_15_10_0", "south", 0, 1);
    add_row_exit(SECTOR_PATH(14,9,0)+"wr_14_9_0", "east", 0, 1);
    add_row_exit(SECTOR_PATH(14,8,0)+"wr_14_8_0", "northeast", 0, 1);
    add_row_exit(SECTOR_PATH(14,10,0)+"wr_14_10_0", "southeast", 0, 1);
}
