/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/sea/std/sector_1_0_3_room";

void
create_water_room()
{
    make_the_room("\n", 14, 7, 3);

    add_swim_exit(SECTOR_PATH(14,6,3)+"wr_14_6_3", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(14,8,3)+"wr_14_8_3", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(13,7,3)+"wr_13_7_3", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(15,7,3)+"wr_15_7_3", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(13,6,3)+"wr_13_6_3", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(13,8,3)+"wr_13_8_3", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(15,6,3)+"wr_15_6_3", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(15,8,3)+"wr_15_8_3", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(14,7,2)+"wr_14_7_2", "up", 0, 0);
    add_swim_exit(SECTOR_PATH(14,7,4)+"wr_14_7_4", "down", 0, 2);
}
