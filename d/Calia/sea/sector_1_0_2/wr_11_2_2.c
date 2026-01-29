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
    make_the_room("\n", 11, 2, 2);

    add_swim_exit(SECTOR_PATH(11,1,2)+"wr_11_1_2", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(11,3,2)+"wr_11_3_2", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(10,2,2)+"wr_10_2_2", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(12,2,2)+"wr_12_2_2", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(10,1,2)+"wr_10_1_2", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(10,3,2)+"wr_10_3_2", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(12,1,2)+"wr_12_1_2", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(12,3,2)+"wr_12_3_2", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(11,2,1)+"wr_11_2_1", "up", 0, 0);
    add_swim_exit(SECTOR_PATH(11,2,3)+"wr_11_2_3", "down", 0, 2);
}
