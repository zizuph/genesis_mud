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
    make_the_room("\n", 10, 5, 0);

    add_swim_exit(SECTOR_PATH(10,4,0)+"wr_10_4_0", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(10,6,0)+"wr_10_6_0", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(9,5,0)+"wr_9_5_0", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(11,5,0)+"wr_11_5_0", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(9,4,0)+"wr_9_4_0", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(9,6,0)+"wr_9_6_0", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(11,4,0)+"wr_11_4_0", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(11,6,0)+"wr_11_6_0", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(10,5,1)+"wr_10_5_1", "down", 0, 2);
    add_row_exit(SECTOR_PATH(10,4,0)+"wr_10_4_0", "north", 0, 1);
    add_row_exit(SECTOR_PATH(10,6,0)+"wr_10_6_0", "south", 0, 1);
    add_row_exit(SECTOR_PATH(9,5,0)+"wr_9_5_0", "east", 0, 1);
    add_row_exit(SECTOR_PATH(11,5,0)+"wr_11_5_0", "west", 0, 1);
    add_row_exit(SECTOR_PATH(9,4,0)+"wr_9_4_0", "northeast", 0, 1);
    add_row_exit(SECTOR_PATH(9,6,0)+"wr_9_6_0", "southeast", 0, 1);
    add_row_exit(SECTOR_PATH(11,4,0)+"wr_11_4_0", "northwest", 0, 1);
    add_row_exit(SECTOR_PATH(11,6,0)+"wr_11_6_0", "southwest", 0, 1);
}
