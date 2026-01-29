/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/sea/std/sector_1_1_4_room";

void
create_water_room()
{
    make_the_room("\n", 14, 13, 4);

    add_swim_exit(SECTOR_PATH(14,12,4)+"wr_14_12_4", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(13,13,4)+"wr_13_13_4", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(13,12,4)+"wr_13_12_4", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(13,14,4)+"wr_13_14_4", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(15,12,4)+"wr_15_12_4", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(14,13,3)+"wr_14_13_3", "up", 0, 0);
}
