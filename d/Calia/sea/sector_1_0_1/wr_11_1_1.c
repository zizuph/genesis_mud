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
    make_the_room("\n", 11, 1, 1);

    add_swim_exit(SECTOR_PATH(11,0,1)+"wr_11_0_1", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(11,2,1)+"wr_11_2_1", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(10,1,1)+"wr_10_1_1", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(12,1,1)+"wr_12_1_1", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(10,0,1)+"wr_10_0_1", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(10,2,1)+"wr_10_2_1", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(12,0,1)+"wr_12_0_1", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(12,2,1)+"wr_12_2_1", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(11,1,0)+"wr_11_1_0", "up", 0, 0);
    add_swim_exit(SECTOR_PATH(11,1,2)+"wr_11_1_2", "down", 0, 2);
}
