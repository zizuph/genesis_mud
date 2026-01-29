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
    make_the_room("\n", 9, 0, 1);

    add_swim_exit(SECTOR_PATH(9,1,1)+"wr_9_1_1", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(8,0,1)+"wr_8_0_1", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(10,0,1)+"wr_10_0_1", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(8,1,1)+"wr_8_1_1", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(10,1,1)+"wr_10_1_1", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(9,0,0)+"wr_9_0_0", "up", 0, 0);
    add_swim_exit(SECTOR_PATH(9,0,2)+"wr_9_0_2", "down", 0, 2);
}
