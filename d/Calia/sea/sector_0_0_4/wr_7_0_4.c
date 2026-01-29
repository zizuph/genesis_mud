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
    make_the_room("\n", 7, 0, 4);

    add_swim_exit(SECTOR_PATH(7,1,4)+"wr_7_1_4", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(6,0,4)+"wr_6_0_4", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(8,0,4)+"wr_8_0_4", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(6,1,4)+"wr_6_1_4", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(8,1,4)+"wr_8_1_4", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(7,0,3)+"wr_7_0_3", "up", 0, 0);
}
