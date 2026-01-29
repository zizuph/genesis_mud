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
    make_the_room("\n", 10, 15, 4);

    add_swim_exit(SECTOR_PATH(10,14,4)+"wr_10_14_4", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(9,15,4)+"wr_9_15_4", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(11,15,4)+"wr_11_15_4", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(9,14,4)+"wr_9_14_4", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(11,14,4)+"wr_11_14_4", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(10,15,3)+"wr_10_15_3", "up", 0, 0);
}
