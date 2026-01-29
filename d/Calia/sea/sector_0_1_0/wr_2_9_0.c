/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/sea/std/sector_0_1_0_room";

void
create_water_room()
{
    make_the_room("\n", 2, 9, 0);

    add_swim_exit(SECTOR_PATH(2,8,0)+"wr_2_8_0", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(2,10,0)+"wr_2_10_0", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(1,9,0)+"wr_1_9_0", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(3,9,0)+"wr_3_9_0", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(1,8,0)+"wr_1_8_0", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(1,10,0)+"wr_1_10_0", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(3,8,0)+"wr_3_8_0", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(3,10,0)+"wr_3_10_0", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(2,9,1)+"wr_2_9_1", "down", 0, 2);
    add_row_exit(SECTOR_PATH(2,8,0)+"wr_2_8_0", "north", 0, 1);
    add_row_exit(SECTOR_PATH(2,10,0)+"wr_2_10_0", "south", 0, 1);
    add_row_exit(SECTOR_PATH(1,9,0)+"wr_1_9_0", "east", 0, 1);
    add_row_exit(SECTOR_PATH(3,9,0)+"wr_3_9_0", "west", 0, 1);
    add_row_exit(SECTOR_PATH(1,8,0)+"wr_1_8_0", "northeast", 0, 1);
    add_row_exit(SECTOR_PATH(1,10,0)+"wr_1_10_0", "southeast", 0, 1);
    add_row_exit(SECTOR_PATH(3,8,0)+"wr_3_8_0", "northwest", 0, 1);
    add_row_exit(SECTOR_PATH(3,10,0)+"wr_3_10_0", "southwest", 0, 1);
}
