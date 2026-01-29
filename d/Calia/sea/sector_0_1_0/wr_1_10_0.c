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
    make_the_room("\n", 1, 10, 0);

    add_wade_exit(SECTOR_PATH(1,9,0)+"wr_1_9_0", "north", 0, 1);
    add_wade_exit(SECTOR_PATH(1,11,0)+"wr_1_11_0", "south", 0, 1);
    add_wade_exit(SECTOR_PATH(0,10,0)+"wr_0_10_0", "east", 0, 1);
    add_wade_exit(SECTOR_PATH(2,10,0)+"wr_2_10_0", "west", 0, 1);
    add_wade_exit(SECTOR_PATH(0,9,0)+"wr_0_9_0", "northeast", 0, 1);
    add_wade_exit(SECTOR_PATH(0,11,0)+"wr_0_11_0", "southeast", 0, 1);
    add_wade_exit(SECTOR_PATH(2,9,0)+"wr_2_9_0", "northwest", 0, 1);
    add_wade_exit(SECTOR_PATH(2,11,0)+"wr_2_11_0", "southwest", 0, 1);
    add_row_exit(SECTOR_PATH(1,9,0)+"wr_1_9_0", "north", 0, 1);
    add_row_exit(SECTOR_PATH(1,11,0)+"wr_1_11_0", "south", 0, 1);
    add_row_exit(SECTOR_PATH(0,10,0)+"wr_0_10_0", "east", 0, 1);
    add_row_exit(SECTOR_PATH(2,10,0)+"wr_2_10_0", "west", 0, 1);
    add_row_exit(SECTOR_PATH(0,9,0)+"wr_0_9_0", "northeast", 0, 1);
    add_row_exit(SECTOR_PATH(0,11,0)+"wr_0_11_0", "southeast", 0, 1);
    add_row_exit(SECTOR_PATH(2,9,0)+"wr_2_9_0", "northwest", 0, 1);
    add_row_exit(SECTOR_PATH(2,11,0)+"wr_2_11_0", "southwest", 0, 1);
}
