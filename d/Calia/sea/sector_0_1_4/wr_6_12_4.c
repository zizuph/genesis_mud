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
    make_the_room("\n", 6, 12, 4);

    add_swim_exit(SECTOR_PATH(6,11,4)+"wr_6_11_4", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(6,13,4)+"wr_6_13_4", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(7,12,4)+"wr_7_12_4", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(7,11,4)+"wr_7_11_4", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(7,13,4)+"wr_7_13_4", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(6,12,3)+"wr_6_12_3", "up", 0, 0);
}
