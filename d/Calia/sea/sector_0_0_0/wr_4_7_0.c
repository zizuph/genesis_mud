/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/sea/std/sector_0_0_0_room";

void
create_water_room()
{
    make_the_room("\n", 4, 7, 0);

    add_swim_exit(SECTOR_PATH(4,6,0)+"wr_4_6_0", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(4,8,0)+"wr_4_8_0", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(3,7,0)+"wr_3_7_0", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(5,7,0)+"wr_5_7_0", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(3,6,0)+"wr_3_6_0", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(3,8,0)+"wr_3_8_0", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(5,6,0)+"wr_5_6_0", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(5,8,0)+"wr_5_8_0", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(4,7,1)+"wr_4_7_1", "down", 0, 2);
    add_row_exit(SECTOR_PATH(4,6,0)+"wr_4_6_0", "north", 0, 1);
    add_row_exit(SECTOR_PATH(4,8,0)+"wr_4_8_0", "south", 0, 1);
    add_row_exit(SECTOR_PATH(3,7,0)+"wr_3_7_0", "east", 0, 1);
    add_row_exit(SECTOR_PATH(5,7,0)+"wr_5_7_0", "west", 0, 1);
    add_row_exit(SECTOR_PATH(3,6,0)+"wr_3_6_0", "northeast", 0, 1);
    add_row_exit(SECTOR_PATH(3,8,0)+"wr_3_8_0", "southeast", 0, 1);
    add_row_exit(SECTOR_PATH(5,6,0)+"wr_5_6_0", "northwest", 0, 1);
    add_row_exit(SECTOR_PATH(5,8,0)+"wr_5_8_0", "southwest", 0, 1);
}
