/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/sea/std/sector_1_1_1_room";

void
create_water_room()
{
    make_the_room("\n", 13, 10, 1);

    add_swim_exit(SECTOR_PATH(13,9,1)+"wr_13_9_1", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(13,11,1)+"wr_13_11_1", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(12,10,1)+"wr_12_10_1", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(14,10,1)+"wr_14_10_1", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(12,9,1)+"wr_12_9_1", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(12,11,1)+"wr_12_11_1", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(14,9,1)+"wr_14_9_1", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(14,11,1)+"wr_14_11_1", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(13,10,0)+"wr_13_10_0", "up", 0, 0);
    add_swim_exit(SECTOR_PATH(13,10,2)+"wr_13_10_2", "down", 0, 2);
}
