/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/sea/std/sector_1_0_0_room";

void
create_water_room()
{
    make_the_room("\n", 15, 3, 0);

    add_swim_exit(SECTOR_PATH(15,4,0)+"wr_15_4_0", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(14,3,0)+"wr_14_3_0", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(14,2,0)+"wr_14_2_0", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(14,4,0)+"wr_14_4_0", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(15,3,1)+"wr_15_3_1", "down", 0, 2);
    add_row_exit(SECTOR_PATH(15,4,0)+"wr_15_4_0", "south", 0, 1);
    add_row_exit(SECTOR_PATH(14,3,0)+"wr_14_3_0", "east", 0, 1);
    add_row_exit(SECTOR_PATH(14,2,0)+"wr_14_2_0", "northeast", 0, 1);
    add_row_exit(SECTOR_PATH(14,4,0)+"wr_14_4_0", "southeast", 0, 1);
}
