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
    make_the_room("\n", 11, 0, 3);

    add_swim_exit(SECTOR_PATH(11,1,3)+"wr_11_1_3", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(10,0,3)+"wr_10_0_3", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(12,0,3)+"wr_12_0_3", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(10,1,3)+"wr_10_1_3", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(12,1,3)+"wr_12_1_3", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(11,0,2)+"wr_11_0_2", "up", 0, 0);
    add_swim_exit(SECTOR_PATH(11,0,4)+"wr_11_0_4", "down", 0, 2);
}
