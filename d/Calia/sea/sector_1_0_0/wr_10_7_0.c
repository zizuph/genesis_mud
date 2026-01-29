
/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

*/

inherit "/d/Calia/sea/std/sector_1_0_0_room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"
#include "turtle.h"


void
create_water_room()
{
    make_the_room("\n", 10, 7, 0);

    add_swim_exit(SECTOR_PATH(10,6,0)+"wr_10_6_0", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(10,8,0)+"wr_10_8_0", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(9,7,0)+"wr_9_7_0", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(11,7,0)+"wr_11_7_0", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(9,6,0)+"wr_9_6_0", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(9,8,0)+"wr_9_8_0", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(11,6,0)+"wr_11_6_0", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(11,8,0)+"wr_11_8_0", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(10,7,1)+"wr_10_7_1", "down", 0, 2);
    add_row_exit(SECTOR_PATH(10,6,0)+"wr_10_6_0", "north", 0, 1);
    add_row_exit(SECTOR_PATH(10,8,0)+"wr_10_8_0", "south", 0, 1);
    add_row_exit(SECTOR_PATH(9,7,0)+"wr_9_7_0", "east", 0, 1);
    add_row_exit(SECTOR_PATH(11,7,0)+"wr_11_7_0", "west", 0, 1);
    add_row_exit(SECTOR_PATH(9,6,0)+"wr_9_6_0", "northeast", 0, 1);
    add_row_exit(SECTOR_PATH(9,8,0)+"wr_9_8_0", "southeast", 0, 1);
    add_row_exit(SECTOR_PATH(11,6,0)+"wr_11_6_0", "northwest", 0, 1);
    add_row_exit(SECTOR_PATH(11,8,0)+"wr_11_8_0", "southwest", 0, 1);

    reset_room(); 
}

