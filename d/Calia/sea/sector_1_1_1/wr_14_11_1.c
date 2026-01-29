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
    make_the_room("\n", 14, 11, 1);

    add_swim_exit(SECTOR_PATH(14,10,1)+"wr_14_10_1", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(14,12,1)+"wr_14_12_1", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(13,11,1)+"wr_13_11_1", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(15,11,1)+"wr_15_11_1", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(13,10,1)+"wr_13_10_1", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(13,12,1)+"wr_13_12_1", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(15,10,1)+"wr_15_10_1", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(15,12,1)+"wr_15_12_1", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(14,11,0)+"wr_14_11_0", "up", 0, 0);
    add_swim_exit(SECTOR_PATH(14,11,2)+"wr_14_11_2", "down", 0, 2);
}
