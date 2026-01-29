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
    make_the_room("\n", 12, 7, 3);

    add_swim_exit(SECTOR_PATH(12,6,3)+"wr_12_6_3", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(12,8,3)+"wr_12_8_3", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(11,7,3)+"wr_11_7_3", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(13,7,3)+"wr_13_7_3", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(11,6,3)+"wr_11_6_3", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(11,8,3)+"wr_11_8_3", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(13,6,3)+"wr_13_6_3", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(13,8,3)+"wr_13_8_3", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(12,7,2)+"wr_12_7_2", "up", 0, 0);
    add_swim_exit(SECTOR_PATH(12,7,4)+"wr_12_7_4", "down", 0, 2);
}
