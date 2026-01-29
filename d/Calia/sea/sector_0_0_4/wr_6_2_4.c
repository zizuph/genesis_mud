/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/sea/std/sector_0_0_4_room";

void
create_water_room()
{
    make_the_room("\n", 6, 2, 4);

    add_swim_exit(SECTOR_PATH(6,1,4)+"wr_6_1_4", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(6,3,4)+"wr_6_3_4", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(7,2,4)+"wr_7_2_4", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(7,1,4)+"wr_7_1_4", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(7,3,4)+"wr_7_3_4", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(6,2,3)+"wr_6_2_3", "up", 0, 0);
}
