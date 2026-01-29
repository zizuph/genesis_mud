/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/sea/std/sector_0_1_3_room";

void
create_water_room()
{
    make_the_room("\n", 5, 10, 3);

    add_swim_exit(SECTOR_PATH(5,9,3)+"wr_5_9_3", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(5,11,3)+"wr_5_11_3", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(6,10,3)+"wr_6_10_3", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(6,9,3)+"wr_6_9_3", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(6,11,3)+"wr_6_11_3", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(5,10,2)+"wr_5_10_2", "up", 0, 0);
}
