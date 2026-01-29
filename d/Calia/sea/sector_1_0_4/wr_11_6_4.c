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
    make_the_room("\n", 11, 6, 4);

    add_swim_exit(SECTOR_PATH(11,5,4)+"wr_11_5_4", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(11,7,4)+"wr_11_7_4", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(10,6,4)+"wr_10_6_4", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(12,6,4)+"wr_12_6_4", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(10,5,4)+"wr_10_5_4", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(10,7,4)+"wr_10_7_4", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(12,5,4)+"wr_12_5_4", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(12,7,4)+"wr_12_7_4", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(11,6,3)+"wr_11_6_3", "up", 0, 0);
}
