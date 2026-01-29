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
    make_the_room("\n", 3, 8, 2);

    add_swim_exit(SECTOR_PATH(3,7,2)+"wr_3_7_2", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(3,9,2)+"wr_3_9_2", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(4,8,2)+"wr_4_8_2", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(4,7,2)+"wr_4_7_2", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(4,9,2)+"wr_4_9_2", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(3,8,1)+"wr_3_8_1", "up", 0, 0);
}
