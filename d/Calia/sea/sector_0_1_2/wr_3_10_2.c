/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/sea/std/sector_0_1_2_room";

void
create_water_room()
{
    make_the_room("\n", 3, 10, 2);

    add_swim_exit(SECTOR_PATH(3,9,2)+"wr_3_9_2", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(3,11,2)+"wr_3_11_2", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(4,10,2)+"wr_4_10_2", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(4,9,2)+"wr_4_9_2", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(4,11,2)+"wr_4_11_2", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(3,10,1)+"wr_3_10_1", "up", 0, 0);
}
