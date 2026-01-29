/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/sea/std/sector_0_0_1_room";

void
create_water_room()
{
    make_the_room("\n", 2, 7, 1);

    add_swim_exit(SECTOR_PATH(2,6,1)+"wr_2_6_1", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(2,8,1)+"wr_2_8_1", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(3,7,1)+"wr_3_7_1", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(3,6,1)+"wr_3_6_1", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(3,8,1)+"wr_3_8_1", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(2,7,0)+"wr_2_7_0", "up", 0, 0);
}
