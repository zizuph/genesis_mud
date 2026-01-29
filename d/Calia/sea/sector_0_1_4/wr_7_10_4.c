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
    make_the_room("\n", 7, 10, 4);

    add_swim_exit(SECTOR_PATH(7,9,4)+"wr_7_9_4", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(7,11,4)+"wr_7_11_4", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(6,10,4)+"wr_6_10_4", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(8,10,4)+"wr_8_10_4", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(6,9,4)+"wr_6_9_4", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(6,11,4)+"wr_6_11_4", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(8,9,4)+"wr_8_9_4", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(8,11,4)+"wr_8_11_4", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(7,10,3)+"wr_7_10_3", "up", 0, 0);
}
