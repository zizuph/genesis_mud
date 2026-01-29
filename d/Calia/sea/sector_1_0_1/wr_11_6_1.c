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
    make_the_room("\n", 11, 6, 1);

    add_swim_exit(SECTOR_PATH(11,5,1)+"wr_11_5_1", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(11,7,1)+"wr_11_7_1", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(10,6,1)+"wr_10_6_1", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(12,6,1)+"wr_12_6_1", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(10,5,1)+"wr_10_5_1", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(10,7,1)+"wr_10_7_1", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(12,5,1)+"wr_12_5_1", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(12,7,1)+"wr_12_7_1", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(11,6,0)+"wr_11_6_0", "up", 0, 0);
    add_swim_exit(SECTOR_PATH(11,6,2)+"wr_11_6_2", "down", 0, 2);
}
