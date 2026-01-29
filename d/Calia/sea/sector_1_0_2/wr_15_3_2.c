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
    make_the_room("\n", 15, 3, 2);

    add_swim_exit(SECTOR_PATH(15,4,2)+"wr_15_4_2", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(14,3,2)+"wr_14_3_2", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(14,2,2)+"wr_14_2_2", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(14,4,2)+"wr_14_4_2", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(15,3,1)+"wr_15_3_1", "up", 0, 0);
    add_swim_exit(SECTOR_PATH(15,3,3)+"wr_15_3_3", "down", 0, 2);
}
