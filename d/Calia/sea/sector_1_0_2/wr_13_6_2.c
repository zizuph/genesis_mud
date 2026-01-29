/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/sea/std/sector_1_0_2_room";

void
create_water_room()
{
    make_the_room("\n", 13, 6, 2);

    add_swim_exit(SECTOR_PATH(13,5,2)+"wr_13_5_2", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(13,7,2)+"wr_13_7_2", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(12,6,2)+"wr_12_6_2", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(14,6,2)+"wr_14_6_2", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(12,5,2)+"wr_12_5_2", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(12,7,2)+"wr_12_7_2", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(14,5,2)+"wr_14_5_2", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(14,7,2)+"wr_14_7_2", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(13,6,1)+"wr_13_6_1", "up", 0, 0);
    add_swim_exit(SECTOR_PATH(13,6,3)+"wr_13_6_3", "down", 0, 2);
}
