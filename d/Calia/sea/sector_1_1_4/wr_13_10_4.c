/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/sea/std/sector_1_1_4_room";

void
create_water_room()
{
    make_the_room("\n", 13, 10, 4);

    add_swim_exit(SECTOR_PATH(13,9,4)+"wr_13_9_4", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(13,11,4)+"wr_13_11_4", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(12,10,4)+"wr_12_10_4", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(14,10,4)+"wr_14_10_4", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(12,9,4)+"wr_12_9_4", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(12,11,4)+"wr_12_11_4", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(14,9,4)+"wr_14_9_4", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(14,11,4)+"wr_14_11_4", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(13,10,3)+"wr_13_10_3", "up", 0, 0);
}
