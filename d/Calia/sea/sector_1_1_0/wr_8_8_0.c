/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/sea/std/sector_1_1_0_room";

void
create_water_room()
{
    make_the_room("\n", 8, 8, 0);

    add_swim_exit(SECTOR_PATH(8,7,0)+"wr_8_7_0", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(8,9,0)+"wr_8_9_0", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(7,8,0)+"wr_7_8_0", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(9,8,0)+"wr_9_8_0", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(7,7,0)+"wr_7_7_0", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(7,9,0)+"wr_7_9_0", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(9,7,0)+"wr_9_7_0", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(9,9,0)+"wr_9_9_0", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(8,8,1)+"wr_8_8_1", "down", 0, 2);
    add_row_exit(SECTOR_PATH(8,7,0)+"wr_8_7_0", "north", 0, 1);
    add_row_exit(SECTOR_PATH(8,9,0)+"wr_8_9_0", "south", 0, 1);
    add_row_exit(SECTOR_PATH(7,8,0)+"wr_7_8_0", "east", 0, 1);
    add_row_exit(SECTOR_PATH(9,8,0)+"wr_9_8_0", "west", 0, 1);
    add_row_exit(SECTOR_PATH(7,7,0)+"wr_7_7_0", "northeast", 0, 1);
    add_row_exit(SECTOR_PATH(7,9,0)+"wr_7_9_0", "southeast", 0, 1);
    add_row_exit(SECTOR_PATH(9,7,0)+"wr_9_7_0", "northwest", 0, 1);
    add_row_exit(SECTOR_PATH(9,9,0)+"wr_9_9_0", "southwest", 0, 1);
}
