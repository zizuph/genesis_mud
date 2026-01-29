/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/sea/std/sector_1_1_4_room";

void
create_water_room()
{
    make_the_room("\n", 10, 8, 4);

    add_swim_exit(SECTOR_PATH(10,7,4)+"wr_10_7_4", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(10,9,4)+"wr_10_9_4", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(9,8,4)+"wr_9_8_4", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(11,8,4)+"wr_11_8_4", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(9,7,4)+"wr_9_7_4", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(9,9,4)+"wr_9_9_4", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(11,7,4)+"wr_11_7_4", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(11,9,4)+"wr_11_9_4", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(10,8,3)+"wr_10_8_3", "up", 0, 0);
}
