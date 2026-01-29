/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/sea/std/sector_1_1_1_room";

void
create_water_room()
{
    make_the_room("\n", 15, 10, 1);

    add_swim_exit(SECTOR_PATH(15,9,1)+"wr_15_9_1", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(15,11,1)+"wr_15_11_1", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(14,10,1)+"wr_14_10_1", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(14,9,1)+"wr_14_9_1", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(14,11,1)+"wr_14_11_1", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(15,10,0)+"wr_15_10_0", "up", 0, 0);
    add_swim_exit(SECTOR_PATH(15,10,2)+"wr_15_10_2", "down", 0, 2);
}
