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
    make_the_room("\n", 10, 2, 0);

    add_swim_exit(SECTOR_PATH(10,1,0)+"wr_10_1_0", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(10,3,0)+"wr_10_3_0", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(9,2,0)+"wr_9_2_0", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(11,2,0)+"wr_11_2_0", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(9,1,0)+"wr_9_1_0", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(9,3,0)+"wr_9_3_0", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(11,1,0)+"wr_11_1_0", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(11,3,0)+"wr_11_3_0", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(10,2,1)+"wr_10_2_1", "down", 0, 2);
    add_row_exit(SECTOR_PATH(10,1,0)+"wr_10_1_0", "north", 0, 1);
    add_row_exit(SECTOR_PATH(10,3,0)+"wr_10_3_0", "south", 0, 1);
    add_row_exit(SECTOR_PATH(9,2,0)+"wr_9_2_0", "east", 0, 1);
    add_row_exit(SECTOR_PATH(11,2,0)+"wr_11_2_0", "west", 0, 1);
    add_row_exit(SECTOR_PATH(9,1,0)+"wr_9_1_0", "northeast", 0, 1);
    add_row_exit(SECTOR_PATH(9,3,0)+"wr_9_3_0", "southeast", 0, 1);
    add_row_exit(SECTOR_PATH(11,1,0)+"wr_11_1_0", "northwest", 0, 1);
    add_row_exit(SECTOR_PATH(11,3,0)+"wr_11_3_0", "southwest", 0, 1);
}
