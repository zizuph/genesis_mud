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
    make_the_room("\n", 12, 15, 1);

    add_swim_exit(SECTOR_PATH(12,14,1)+"wr_12_14_1", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(11,15,1)+"wr_11_15_1", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(11,14,1)+"wr_11_14_1", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(13,14,1)+"wr_13_14_1", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(12,15,0)+"wr_12_15_0", "up", 0, 0);
    add_swim_exit(SECTOR_PATH(12,15,2)+"wr_12_15_2", "down", 0, 2);
}
