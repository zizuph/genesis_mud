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
    make_the_room("\n", 10, 5, 2);

    add_swim_exit(SECTOR_PATH(10,4,2)+"wr_10_4_2", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(10,6,2)+"wr_10_6_2", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(9,5,2)+"wr_9_5_2", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(11,5,2)+"wr_11_5_2", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(9,4,2)+"wr_9_4_2", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(9,6,2)+"wr_9_6_2", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(11,4,2)+"wr_11_4_2", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(11,6,2)+"wr_11_6_2", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(10,5,1)+"wr_10_5_1", "up", 0, 0);
    add_swim_exit(SECTOR_PATH(10,5,3)+"wr_10_5_3", "down", 0, 2);
}
