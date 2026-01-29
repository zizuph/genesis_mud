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
    make_the_room("\n", 10, 0, 4);

    add_swim_exit(SECTOR_PATH(10,1,4)+"wr_10_1_4", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(9,0,4)+"wr_9_0_4", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(11,0,4)+"wr_11_0_4", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(9,1,4)+"wr_9_1_4", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(11,1,4)+"wr_11_1_4", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(10,0,3)+"wr_10_0_3", "up", 0, 0);
}
