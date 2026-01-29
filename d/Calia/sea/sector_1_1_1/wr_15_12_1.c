/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/sea/std/sector_1_1_1_room";

void
create_water_room()
{
    make_the_room("\n", 15, 12, 1);

    add_swim_exit(SECTOR_PATH(15,11,1)+"wr_15_11_1", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(14,12,1)+"wr_14_12_1", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(14,11,1)+"wr_14_11_1", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(14,13,1)+"wr_14_13_1", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(15,12,0)+"wr_15_12_0", "up", 0, 0);
    add_swim_exit(SECTOR_PATH(15,12,2)+"wr_15_12_2", "down", 0, 2);
}
