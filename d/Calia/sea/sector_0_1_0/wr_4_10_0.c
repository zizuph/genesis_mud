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
    make_the_room("\n", 4, 10, 0);

    add_swim_exit(SECTOR_PATH(4,9,0)+"wr_4_9_0", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(4,11,0)+"wr_4_11_0", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(3,10,0)+"wr_3_10_0", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(5,10,0)+"wr_5_10_0", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(3,9,0)+"wr_3_9_0", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(3,11,0)+"wr_3_11_0", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(5,9,0)+"wr_5_9_0", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(5,11,0)+"wr_5_11_0", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(4,10,1)+"wr_4_10_1", "down", 0, 2);
    add_row_exit(SECTOR_PATH(4,9,0)+"wr_4_9_0", "north", 0, 1);
    add_row_exit(SECTOR_PATH(4,11,0)+"wr_4_11_0", "south", 0, 1);
    add_row_exit(SECTOR_PATH(3,10,0)+"wr_3_10_0", "east", 0, 1);
    add_row_exit(SECTOR_PATH(5,10,0)+"wr_5_10_0", "west", 0, 1);
    add_row_exit(SECTOR_PATH(3,9,0)+"wr_3_9_0", "northeast", 0, 1);
    add_row_exit(SECTOR_PATH(3,11,0)+"wr_3_11_0", "southeast", 0, 1);
    add_row_exit(SECTOR_PATH(5,9,0)+"wr_5_9_0", "northwest", 0, 1);
    add_row_exit(SECTOR_PATH(5,11,0)+"wr_5_11_0", "southwest", 0, 1);
}
