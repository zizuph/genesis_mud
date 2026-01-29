/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/sea/std/sector_1_0_4_room";

void
create_water_room()
{
    make_the_room("\n", 15, 3, 4);

    add_swim_exit(SECTOR_PATH(15,4,4)+"wr_15_4_4", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(14,3,4)+"wr_14_3_4", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(14,2,4)+"wr_14_2_4", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(14,4,4)+"wr_14_4_4", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(15,3,3)+"wr_15_3_3", "up", 0, 0);
}
