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
    make_the_room("\n", 14, 13, 0);

    add_swim_exit(SECTOR_PATH(14,12,0)+"wr_14_12_0", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(13,13,0)+"wr_13_13_0", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(13,12,0)+"wr_13_12_0", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(13,14,0)+"wr_13_14_0", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(15,12,0)+"wr_15_12_0", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(14,13,1)+"wr_14_13_1", "down", 0, 2);
    add_row_exit(SECTOR_PATH(14,12,0)+"wr_14_12_0", "north", 0, 1);
    add_row_exit(SECTOR_PATH(13,13,0)+"wr_13_13_0", "east", 0, 1);
    add_row_exit(SECTOR_PATH(13,12,0)+"wr_13_12_0", "northeast", 0, 1);
    add_row_exit(SECTOR_PATH(13,14,0)+"wr_13_14_0", "southeast", 0, 1);
    add_row_exit(SECTOR_PATH(15,12,0)+"wr_15_12_0", "northwest", 0, 1);
}
