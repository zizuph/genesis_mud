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
    make_the_room("\n", 13, 2, 3);

    add_swim_exit(SECTOR_PATH(13,1,3)+"wr_13_1_3", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(13,3,3)+"wr_13_3_3", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(12,2,3)+"wr_12_2_3", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(14,2,3)+"wr_14_2_3", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(12,1,3)+"wr_12_1_3", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(12,3,3)+"wr_12_3_3", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(14,3,3)+"wr_14_3_3", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(13,2,2)+"wr_13_2_2", "up", 0, 0);
    add_swim_exit(SECTOR_PATH(13,2,4)+"wr_13_2_4", "down", 0, 2);
}
