/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/sea/std/sector_1_0_4_room";

void
create_water_room()
{
    make_the_room("\n", 10, 5, 4);

    add_swim_exit(SECTOR_PATH(10,4,4)+"wr_10_4_4", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(10,6,4)+"wr_10_6_4", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(9,5,4)+"wr_9_5_4", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(11,5,4)+"wr_11_5_4", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(9,4,4)+"wr_9_4_4", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(9,6,4)+"wr_9_6_4", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(11,4,4)+"wr_11_4_4", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(11,6,4)+"wr_11_6_4", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(10,5,3)+"wr_10_5_3", "up", 0, 0);
}
