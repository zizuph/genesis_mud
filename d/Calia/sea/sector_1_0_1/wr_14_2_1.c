/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/sea/std/sector_1_0_1_room";

void
create_water_room()
{
    make_the_room("\n", 14, 2, 1);

    add_swim_exit(SECTOR_PATH(14,3,1)+"wr_14_3_1", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(13,2,1)+"wr_13_2_1", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(13,1,1)+"wr_13_1_1", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(13,3,1)+"wr_13_3_1", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(15,3,1)+"wr_15_3_1", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(14,2,0)+"wr_14_2_0", "up", 0, 0);
    add_swim_exit(SECTOR_PATH(14,2,2)+"wr_14_2_2", "down", 0, 2);
}
