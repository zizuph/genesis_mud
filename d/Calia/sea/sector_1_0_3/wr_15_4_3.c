/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/sea/std/sector_1_0_3_room";

void
create_water_room()
{
    make_the_room("\n", 15, 4, 3);

    add_swim_exit(SECTOR_PATH(15,3,3)+"wr_15_3_3", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(15,5,3)+"wr_15_5_3", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(14,4,3)+"wr_14_4_3", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(14,3,3)+"wr_14_3_3", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(14,5,3)+"wr_14_5_3", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(15,4,2)+"wr_15_4_2", "up", 0, 0);
    add_swim_exit(SECTOR_PATH(15,4,4)+"wr_15_4_4", "down", 0, 2);
}
