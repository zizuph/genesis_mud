/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/sea/std/sector_0_0_2_room";

void
create_water_room()
{
    make_the_room("\n", 3, 0, 2);

    add_swim_exit(SECTOR_PATH(3,1,2)+"wr_3_1_2", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(4,0,2)+"wr_4_0_2", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(4,1,2)+"wr_4_1_2", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(3,0,1)+"wr_3_0_1", "up", 0, 0);
}
