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
    make_the_room("\n", 10, 8, 1);

    add_swim_exit(SECTOR_PATH(10,7,1)+"wr_10_7_1", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(10,9,1)+"wr_10_9_1", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(9,8,1)+"wr_9_8_1", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(11,8,1)+"wr_11_8_1", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(9,7,1)+"wr_9_7_1", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(9,9,1)+"wr_9_9_1", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(11,7,1)+"wr_11_7_1", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(11,9,1)+"wr_11_9_1", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(10,8,0)+"wr_10_8_0", "up", 0, 0);
    add_swim_exit(SECTOR_PATH(10,8,2)+"wr_10_8_2", "down", 0, 2);
}
