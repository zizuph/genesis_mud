/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/sea/std/sector_0_0_3_room";

void
create_water_room()
{
    make_the_room("\n", 5, 3, 3);

    add_swim_exit(SECTOR_PATH(5,2,3)+"wr_5_2_3", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(5,4,3)+"wr_5_4_3", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(6,3,3)+"wr_6_3_3", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(6,2,3)+"wr_6_2_3", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(6,4,3)+"wr_6_4_3", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(5,3,2)+"wr_5_3_2", "up", 0, 0);
}
