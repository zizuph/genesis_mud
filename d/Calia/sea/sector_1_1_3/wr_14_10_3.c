/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/sea/std/sector_1_1_3_room";

void
create_water_room()
{
    make_the_room("\n", 14, 10, 3);

    add_swim_exit(SECTOR_PATH(14,9,3)+"wr_14_9_3", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(14,11,3)+"wr_14_11_3", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(13,10,3)+"wr_13_10_3", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(15,10,3)+"wr_15_10_3", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(13,9,3)+"wr_13_9_3", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(13,11,3)+"wr_13_11_3", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(15,9,3)+"wr_15_9_3", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(15,11,3)+"wr_15_11_3", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(14,10,2)+"wr_14_10_2", "up", 0, 0);
    add_swim_exit(SECTOR_PATH(14,10,4)+"wr_14_10_4", "down", 0, 2);
}
