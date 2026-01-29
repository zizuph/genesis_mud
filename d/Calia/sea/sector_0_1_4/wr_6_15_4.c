/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/sea/std/sector_0_1_4_room";

void
create_water_room()
{
    make_the_room("\n", 6, 15, 4);

    add_swim_exit(SECTOR_PATH(6,14,4)+"wr_6_14_4", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(7,15,4)+"wr_7_15_4", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(7,14,4)+"wr_7_14_4", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(6,15,3)+"wr_6_15_3", "up", 0, 0);
}
