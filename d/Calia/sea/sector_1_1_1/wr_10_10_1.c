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
    make_the_room("\n", 10, 10, 1);

    add_swim_exit(SECTOR_PATH(10,9,1)+"wr_10_9_1", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(10,11,1)+"wr_10_11_1", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(9,10,1)+"wr_9_10_1", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(11,10,1)+"wr_11_10_1", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(9,9,1)+"wr_9_9_1", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(9,11,1)+"wr_9_11_1", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(11,9,1)+"wr_11_9_1", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(11,11,1)+"wr_11_11_1", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(10,10,0)+"wr_10_10_0", "up", 0, 0);
    add_swim_exit(SECTOR_PATH(10,10,2)+"wr_10_10_2", "down", 0, 2);
}
