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
    make_the_room("\n", 7, 2, 0);

    add_swim_exit(SECTOR_PATH(7,1,0)+"wr_7_1_0", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(7,3,0)+"wr_7_3_0", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(6,2,0)+"wr_6_2_0", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(8,2,0)+"wr_8_2_0", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(6,1,0)+"wr_6_1_0", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(6,3,0)+"wr_6_3_0", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(8,1,0)+"wr_8_1_0", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(8,3,0)+"wr_8_3_0", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(7,2,1)+"wr_7_2_1", "down", 0, 2);
    add_row_exit(SECTOR_PATH(7,1,0)+"wr_7_1_0", "north", 0, 1);
    add_row_exit(SECTOR_PATH(7,3,0)+"wr_7_3_0", "south", 0, 1);
    add_row_exit(SECTOR_PATH(6,2,0)+"wr_6_2_0", "east", 0, 1);
    add_row_exit(SECTOR_PATH(8,2,0)+"wr_8_2_0", "west", 0, 1);
    add_row_exit(SECTOR_PATH(6,1,0)+"wr_6_1_0", "northeast", 0, 1);
    add_row_exit(SECTOR_PATH(6,3,0)+"wr_6_3_0", "southeast", 0, 1);
    add_row_exit(SECTOR_PATH(8,1,0)+"wr_8_1_0", "northwest", 0, 1);
    add_row_exit(SECTOR_PATH(8,3,0)+"wr_8_3_0", "southwest", 0, 1);
}
