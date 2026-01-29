/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/sea/std/sector_1_0_1_room";

void
create_water_room()
{
    make_the_room("\n", 12, 7, 1);

    add_swim_exit(SECTOR_PATH(12,6,1)+"wr_12_6_1", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(12,8,1)+"wr_12_8_1", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(11,7,1)+"wr_11_7_1", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(13,7,1)+"wr_13_7_1", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(11,6,1)+"wr_11_6_1", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(11,8,1)+"wr_11_8_1", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(13,6,1)+"wr_13_6_1", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(13,8,1)+"wr_13_8_1", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(12,7,0)+"wr_12_7_0", "up", 0, 0);
    add_swim_exit(SECTOR_PATH(12,7,2)+"wr_12_7_2", "down", 0, 2);
}
