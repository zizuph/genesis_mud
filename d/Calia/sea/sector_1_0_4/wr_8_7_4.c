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
    make_the_room("\n", 8, 7, 4);

    add_swim_exit(SECTOR_PATH(8,6,4)+"wr_8_6_4", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(8,8,4)+"wr_8_8_4", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(7,7,4)+"wr_7_7_4", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(9,7,4)+"wr_9_7_4", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(7,6,4)+"wr_7_6_4", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(7,8,4)+"wr_7_8_4", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(9,6,4)+"wr_9_6_4", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(9,8,4)+"wr_9_8_4", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(8,7,3)+"wr_8_7_3", "up", 0, 0);
}
