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
    make_the_room("\n", 2, 1, 1);

    add_swim_exit(SECTOR_PATH(2,2,1)+"wr_2_2_1", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(3,1,1)+"wr_3_1_1", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(3,0,1)+"wr_3_0_1", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(3,2,1)+"wr_3_2_1", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(2,1,0)+"wr_2_1_0", "up", 0, 0);
}
