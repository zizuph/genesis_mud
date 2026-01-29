/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/sea/std/sector_1_1_2_room";

void
create_water_room()
{
    make_the_room("\n", 10, 14, 2);

    add_swim_exit(SECTOR_PATH(10,13,2)+"wr_10_13_2", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(10,15,2)+"wr_10_15_2", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(9,14,2)+"wr_9_14_2", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(11,14,2)+"wr_11_14_2", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(9,13,2)+"wr_9_13_2", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(9,15,2)+"wr_9_15_2", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(11,13,2)+"wr_11_13_2", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(11,15,2)+"wr_11_15_2", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(10,14,1)+"wr_10_14_1", "up", 0, 0);
    add_swim_exit(SECTOR_PATH(10,14,3)+"wr_10_14_3", "down", 0, 2);
}
