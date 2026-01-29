/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/sea/std/sector_1_0_4_room";

void
create_water_room()
{
    make_the_room("\n", 14, 5, 4);

    add_swim_exit(SECTOR_PATH(14,4,4)+"wr_14_4_4", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(14,6,4)+"wr_14_6_4", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(13,5,4)+"wr_13_5_4", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(15,5,4)+"wr_15_5_4", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(13,4,4)+"wr_13_4_4", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(13,6,4)+"wr_13_6_4", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(15,4,4)+"wr_15_4_4", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(15,6,4)+"wr_15_6_4", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(14,5,3)+"wr_14_5_3", "up", 0, 0);
}
