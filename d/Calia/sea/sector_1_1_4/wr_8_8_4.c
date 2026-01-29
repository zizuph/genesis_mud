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
    make_the_room("\n", 8, 8, 4);

    add_swim_exit(SECTOR_PATH(8,7,4)+"wr_8_7_4", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(8,9,4)+"wr_8_9_4", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(7,8,4)+"wr_7_8_4", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(9,8,4)+"wr_9_8_4", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(7,7,4)+"wr_7_7_4", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(7,9,4)+"wr_7_9_4", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(9,7,4)+"wr_9_7_4", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(9,9,4)+"wr_9_9_4", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(8,8,3)+"wr_8_8_3", "up", 0, 0);
}
