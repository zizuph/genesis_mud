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
    make_the_room("\n", 13, 11, 0);

    add_swim_exit(SECTOR_PATH(13,10,0)+"wr_13_10_0", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(13,12,0)+"wr_13_12_0", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(12,11,0)+"wr_12_11_0", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(14,11,0)+"wr_14_11_0", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(12,10,0)+"wr_12_10_0", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(12,12,0)+"wr_12_12_0", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(14,10,0)+"wr_14_10_0", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(14,12,0)+"wr_14_12_0", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(13,11,1)+"wr_13_11_1", "down", 0, 2);
    add_row_exit(SECTOR_PATH(13,10,0)+"wr_13_10_0", "north", 0, 1);
    add_row_exit(SECTOR_PATH(13,12,0)+"wr_13_12_0", "south", 0, 1);
    add_row_exit(SECTOR_PATH(12,11,0)+"wr_12_11_0", "east", 0, 1);
    add_row_exit(SECTOR_PATH(14,11,0)+"wr_14_11_0", "west", 0, 1);
    add_row_exit(SECTOR_PATH(12,10,0)+"wr_12_10_0", "northeast", 0, 1);
    add_row_exit(SECTOR_PATH(12,12,0)+"wr_12_12_0", "southeast", 0, 1);
    add_row_exit(SECTOR_PATH(14,10,0)+"wr_14_10_0", "northwest", 0, 1);
    add_row_exit(SECTOR_PATH(14,12,0)+"wr_14_12_0", "southwest", 0, 1);
}
