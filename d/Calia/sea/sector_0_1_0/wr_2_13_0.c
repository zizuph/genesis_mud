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
    make_the_room("\n", 2, 13, 0);

    add_swim_exit(SECTOR_PATH(2,12,0)+"wr_2_12_0", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(2,14,0)+"wr_2_14_0", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(1,13,0)+"wr_1_13_0", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(3,13,0)+"wr_3_13_0", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(1,12,0)+"wr_1_12_0", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(3,12,0)+"wr_3_12_0", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(3,14,0)+"wr_3_14_0", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(2,13,1)+"wr_2_13_1", "down", 0, 2);
    add_row_exit(SECTOR_PATH(2,12,0)+"wr_2_12_0", "north", 0, 1);
    add_row_exit(SECTOR_PATH(2,14,0)+"wr_2_14_0", "south", 0, 1);
    add_row_exit(SECTOR_PATH(1,13,0)+"wr_1_13_0", "east", 0, 1);
    add_row_exit(SECTOR_PATH(3,13,0)+"wr_3_13_0", "west", 0, 1);
    add_row_exit(SECTOR_PATH(1,12,0)+"wr_1_12_0", "northeast", 0, 1);
    add_row_exit(SECTOR_PATH(3,12,0)+"wr_3_12_0", "northwest", 0, 1);
    add_row_exit(SECTOR_PATH(3,14,0)+"wr_3_14_0", "southwest", 0, 1);
}
