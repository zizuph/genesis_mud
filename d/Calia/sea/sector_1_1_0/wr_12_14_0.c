/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/sea/std/sector_1_1_0_room";

#include "gull.h"

void
create_water_room()
{
    make_the_room("\n", 12, 14, 0);

    add_swim_exit(SECTOR_PATH(12,13,0)+"wr_12_13_0", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(12,15,0)+"wr_12_15_0", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(11,14,0)+"wr_11_14_0", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(13,14,0)+"wr_13_14_0", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(11,13,0)+"wr_11_13_0", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(11,15,0)+"wr_11_15_0", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(13,13,0)+"wr_13_13_0", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(12,14,1)+"wr_12_14_1", "down", 0, 2);
    add_row_exit(SECTOR_PATH(12,13,0)+"wr_12_13_0", "north", 0, 1);
    add_row_exit(SECTOR_PATH(12,15,0)+"wr_12_15_0", "south", 0, 1);
    add_row_exit(SECTOR_PATH(11,14,0)+"wr_11_14_0", "east", 0, 1);
    add_row_exit(SECTOR_PATH(13,14,0)+"wr_13_14_0", "west", 0, 1);
    add_row_exit(SECTOR_PATH(11,13,0)+"wr_11_13_0", "northeast", 0, 1);
    add_row_exit(SECTOR_PATH(11,15,0)+"wr_11_15_0", "southeast", 0, 1);
    add_row_exit(SECTOR_PATH(13,13,0)+"wr_13_13_0", "northwest", 0, 1);
    reset_room();
}
