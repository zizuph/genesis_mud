/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/sea/std/sector_1_0_1_room";

void
create_water_room()
{
    make_the_room("\n", 10, 4, 1);

    add_swim_exit(SECTOR_PATH(10,3,1)+"wr_10_3_1", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(10,5,1)+"wr_10_5_1", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(9,4,1)+"wr_9_4_1", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(11,4,1)+"wr_11_4_1", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(9,3,1)+"wr_9_3_1", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(9,5,1)+"wr_9_5_1", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(11,3,1)+"wr_11_3_1", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(11,5,1)+"wr_11_5_1", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(10,4,0)+"wr_10_4_0", "up", 0, 0);
    add_swim_exit(SECTOR_PATH(10,4,2)+"wr_10_4_2", "down", 0, 2);
}
