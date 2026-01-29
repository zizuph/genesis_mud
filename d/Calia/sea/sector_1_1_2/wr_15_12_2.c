/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/sea/std/sector_1_1_2_room";

void
create_water_room()
{
    make_the_room("\n", 15, 12, 2);

    add_swim_exit(SECTOR_PATH(15,11,2)+"wr_15_11_2", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(14,12,2)+"wr_14_12_2", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(14,11,2)+"wr_14_11_2", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(14,13,2)+"wr_14_13_2", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(15,12,1)+"wr_15_12_1", "up", 0, 0);
    add_swim_exit(SECTOR_PATH(15,12,3)+"wr_15_12_3", "down", 0, 2);
}
