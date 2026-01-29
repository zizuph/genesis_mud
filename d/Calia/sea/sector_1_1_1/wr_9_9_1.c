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
    make_the_room("\n", 9, 9, 1);

    add_swim_exit(SECTOR_PATH(9,8,1)+"wr_9_8_1", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(9,10,1)+"wr_9_10_1", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(8,9,1)+"wr_8_9_1", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(10,9,1)+"wr_10_9_1", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(8,8,1)+"wr_8_8_1", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(8,10,1)+"wr_8_10_1", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(10,8,1)+"wr_10_8_1", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(10,10,1)+"wr_10_10_1", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(9,9,0)+"wr_9_9_0", "up", 0, 0);
    add_swim_exit(SECTOR_PATH(9,9,2)+"wr_9_9_2", "down", 0, 2);
}
