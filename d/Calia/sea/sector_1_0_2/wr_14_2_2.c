/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/sea/std/sector_1_0_2_room";

void
create_water_room()
{
    make_the_room("\n", 14, 2, 2);

    add_swim_exit(SECTOR_PATH(14,3,2)+"wr_14_3_2", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(13,2,2)+"wr_13_2_2", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(13,1,2)+"wr_13_1_2", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(13,3,2)+"wr_13_3_2", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(15,3,2)+"wr_15_3_2", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(14,2,1)+"wr_14_2_1", "up", 0, 0);
    add_swim_exit(SECTOR_PATH(14,2,3)+"wr_14_2_3", "down", 0, 2);
}
