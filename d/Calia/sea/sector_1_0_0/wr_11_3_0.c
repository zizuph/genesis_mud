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
    make_the_room("\n", 11, 3, 0);

    add_swim_exit(SECTOR_PATH(11,2,0)+"wr_11_2_0", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(11,4,0)+"wr_11_4_0", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(10,3,0)+"wr_10_3_0", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(12,3,0)+"wr_12_3_0", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(10,2,0)+"wr_10_2_0", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(10,4,0)+"wr_10_4_0", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(12,2,0)+"wr_12_2_0", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(12,4,0)+"wr_12_4_0", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(11,3,1)+"wr_11_3_1", "down", 0, 2);
    add_row_exit(SECTOR_PATH(11,2,0)+"wr_11_2_0", "north", 0, 1);
    add_row_exit(SECTOR_PATH(11,4,0)+"wr_11_4_0", "south", 0, 1);
    add_row_exit(SECTOR_PATH(10,3,0)+"wr_10_3_0", "east", 0, 1);
    add_row_exit(SECTOR_PATH(12,3,0)+"wr_12_3_0", "west", 0, 1);
    add_row_exit(SECTOR_PATH(10,2,0)+"wr_10_2_0", "northeast", 0, 1);
    add_row_exit(SECTOR_PATH(10,4,0)+"wr_10_4_0", "southeast", 0, 1);
    add_row_exit(SECTOR_PATH(12,2,0)+"wr_12_2_0", "northwest", 0, 1);
    add_row_exit(SECTOR_PATH(12,4,0)+"wr_12_4_0", "southwest", 0, 1);
}
