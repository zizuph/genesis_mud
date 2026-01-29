/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/sea/std/sector_1_0_2_room";

void
create_water_room()
{
    make_the_room("\n", 9, 3, 2);

    add_swim_exit(SECTOR_PATH(9,2,2)+"wr_9_2_2", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(9,4,2)+"wr_9_4_2", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(8,3,2)+"wr_8_3_2", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(10,3,2)+"wr_10_3_2", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(8,2,2)+"wr_8_2_2", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(8,4,2)+"wr_8_4_2", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(10,2,2)+"wr_10_2_2", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(10,4,2)+"wr_10_4_2", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(9,3,1)+"wr_9_3_1", "up", 0, 0);
    add_swim_exit(SECTOR_PATH(9,3,3)+"wr_9_3_3", "down", 0, 2);
}
