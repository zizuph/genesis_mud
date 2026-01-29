/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/sea/std/sector_0_1_1_room";

void
create_water_room()
{
    make_the_room("\n", 2, 14, 1);

    add_swim_exit(SECTOR_PATH(2,13,1)+"wr_2_13_1", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(3,14,1)+"wr_3_14_1", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(3,13,1)+"wr_3_13_1", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(3,15,1)+"wr_3_15_1", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(2,14,0)+"wr_2_14_0", "up", 0, 0);
}
