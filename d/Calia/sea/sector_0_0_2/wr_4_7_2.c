/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/sea/std/sector_0_0_2_room";

void
create_water_room()
{
    make_the_room("\n", 4, 7, 2);

    add_swim_exit(SECTOR_PATH(4,6,2)+"wr_4_6_2", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(4,8,2)+"wr_4_8_2", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(3,7,2)+"wr_3_7_2", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(5,7,2)+"wr_5_7_2", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(3,6,2)+"wr_3_6_2", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(3,8,2)+"wr_3_8_2", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(5,6,2)+"wr_5_6_2", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(5,8,2)+"wr_5_8_2", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(4,7,1)+"wr_4_7_1", "up", 0, 0);
}
