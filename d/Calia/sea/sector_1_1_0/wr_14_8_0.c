/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/sea/std/sector_1_1_0_room";

#include "small_wkroug.h"

void
create_water_room()
{
    make_the_room("\n", 14, 8, 0);

    add_swim_exit(SECTOR_PATH(14,7,0)+"wr_14_7_0", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(14,9,0)+"wr_14_9_0", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(13,8,0)+"wr_13_8_0", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(15,8,0)+"wr_15_8_0", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(13,7,0)+"wr_13_7_0", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(13,9,0)+"wr_13_9_0", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(15,7,0)+"wr_15_7_0", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(15,9,0)+"wr_15_9_0", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(14,8,1)+"wr_14_8_1", "down", 0, 2);
    add_row_exit(SECTOR_PATH(14,7,0)+"wr_14_7_0", "north", 0, 1);
    add_row_exit(SECTOR_PATH(14,9,0)+"wr_14_9_0", "south", 0, 1);
    add_row_exit(SECTOR_PATH(13,8,0)+"wr_13_8_0", "east", 0, 1);
    add_row_exit(SECTOR_PATH(15,8,0)+"wr_15_8_0", "west", 0, 1);
    add_row_exit(SECTOR_PATH(13,7,0)+"wr_13_7_0", "northeast", 0, 1);
    add_row_exit(SECTOR_PATH(13,9,0)+"wr_13_9_0", "southeast", 0, 1);
    add_row_exit(SECTOR_PATH(15,7,0)+"wr_15_7_0", "northwest", 0, 1);
    add_row_exit(SECTOR_PATH(15,9,0)+"wr_15_9_0", "southwest", 0, 1);

    reset_room(); 
}

