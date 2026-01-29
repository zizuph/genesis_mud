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
    make_the_room("\n", 8, 0, 0);

    add_swim_exit(SECTOR_PATH(8,1,0)+"wr_8_1_0", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(7,0,0)+"wr_7_0_0", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(9,0,0)+"wr_9_0_0", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(7,1,0)+"wr_7_1_0", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(9,1,0)+"wr_9_1_0", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(8,0,1)+"wr_8_0_1", "down", 0, 2);
    add_row_exit(SECTOR_PATH(8,1,0)+"wr_8_1_0", "south", 0, 1);
    add_row_exit(SECTOR_PATH(7,0,0)+"wr_7_0_0", "east", 0, 1);
    add_row_exit(SECTOR_PATH(9,0,0)+"wr_9_0_0", "west", 0, 1);
    add_row_exit(SECTOR_PATH(7,1,0)+"wr_7_1_0", "southeast", 0, 1);
    add_row_exit(SECTOR_PATH(9,1,0)+"wr_9_1_0", "southwest", 0, 1);
}
