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
    make_the_room("\n", 2, 11, 1);

    add_swim_exit(SECTOR_PATH(2,10,1)+"wr_2_10_1", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(2,12,1)+"wr_2_12_1", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(3,11,1)+"wr_3_11_1", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(3,10,1)+"wr_3_10_1", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(3,12,1)+"wr_3_12_1", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(2,11,0)+"wr_2_11_0", "up", 0, 0);
}
