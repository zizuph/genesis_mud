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
    make_the_room("\n", 6, 9, 0);

    add_swim_exit(SECTOR_PATH(6,8,0)+"wr_6_8_0", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(6,10,0)+"wr_6_10_0", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(5,9,0)+"wr_5_9_0", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(7,9,0)+"wr_7_9_0", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(5,8,0)+"wr_5_8_0", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(5,10,0)+"wr_5_10_0", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(7,8,0)+"wr_7_8_0", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(7,10,0)+"wr_7_10_0", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(6,9,1)+"wr_6_9_1", "down", 0, 2);
    add_row_exit(SECTOR_PATH(6,8,0)+"wr_6_8_0", "north", 0, 1);
    add_row_exit(SECTOR_PATH(6,10,0)+"wr_6_10_0", "south", 0, 1);
    add_row_exit(SECTOR_PATH(5,9,0)+"wr_5_9_0", "east", 0, 1);
    add_row_exit(SECTOR_PATH(7,9,0)+"wr_7_9_0", "west", 0, 1);
    add_row_exit(SECTOR_PATH(5,8,0)+"wr_5_8_0", "northeast", 0, 1);
    add_row_exit(SECTOR_PATH(5,10,0)+"wr_5_10_0", "southeast", 0, 1);
    add_row_exit(SECTOR_PATH(7,8,0)+"wr_7_8_0", "northwest", 0, 1);
    add_row_exit(SECTOR_PATH(7,10,0)+"wr_7_10_0", "southwest", 0, 1);
}
