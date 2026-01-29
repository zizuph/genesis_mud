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
    make_the_room("\n", 8, 7, 3);

    add_swim_exit(SECTOR_PATH(8,6,3)+"wr_8_6_3", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(8,8,3)+"wr_8_8_3", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(7,7,3)+"wr_7_7_3", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(9,7,3)+"wr_9_7_3", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(7,6,3)+"wr_7_6_3", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(7,8,3)+"wr_7_8_3", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(9,6,3)+"wr_9_6_3", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(9,8,3)+"wr_9_8_3", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(8,7,2)+"wr_8_7_2", "up", 0, 0);
    add_swim_exit(SECTOR_PATH(8,7,4)+"wr_8_7_4", "down", 0, 2);
}
