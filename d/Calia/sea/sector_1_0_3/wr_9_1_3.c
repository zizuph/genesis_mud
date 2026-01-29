/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/sea/std/sector_1_0_3_room";

void
create_water_room()
{
    make_the_room("\n", 9, 1, 3);

    add_swim_exit(SECTOR_PATH(9,0,3)+"wr_9_0_3", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(9,2,3)+"wr_9_2_3", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(8,1,3)+"wr_8_1_3", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(10,1,3)+"wr_10_1_3", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(8,0,3)+"wr_8_0_3", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(8,2,3)+"wr_8_2_3", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(10,0,3)+"wr_10_0_3", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(10,2,3)+"wr_10_2_3", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(9,1,2)+"wr_9_1_2", "up", 0, 0);
    add_swim_exit(SECTOR_PATH(9,1,4)+"wr_9_1_4", "down", 0, 2);
}
