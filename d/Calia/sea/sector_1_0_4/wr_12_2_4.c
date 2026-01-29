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
    make_the_room("\n", 12, 2, 4);

    add_swim_exit(SECTOR_PATH(12,1,4)+"wr_12_1_4", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(12,3,4)+"wr_12_3_4", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(11,2,4)+"wr_11_2_4", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(13,2,4)+"wr_13_2_4", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(11,1,4)+"wr_11_1_4", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(11,3,4)+"wr_11_3_4", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(13,1,4)+"wr_13_1_4", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(13,3,4)+"wr_13_3_4", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(12,2,3)+"wr_12_2_3", "up", 0, 0);
}
