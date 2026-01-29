/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/sea/std/sector_0_0_4_room";

void
create_water_room()
{
    make_the_room("\n", 7, 4, 4);

    add_swim_exit(SECTOR_PATH(7,3,4)+"wr_7_3_4", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(7,5,4)+"wr_7_5_4", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(6,4,4)+"wr_6_4_4", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(8,4,4)+"wr_8_4_4", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(6,3,4)+"wr_6_3_4", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(6,5,4)+"wr_6_5_4", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(8,3,4)+"wr_8_3_4", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(8,5,4)+"wr_8_5_4", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(7,4,3)+"wr_7_4_3", "up", 0, 0);
}
