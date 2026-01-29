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
    make_the_room("\n", 13, 4, 1);

    add_swim_exit(SECTOR_PATH(13,3,1)+"wr_13_3_1", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(13,5,1)+"wr_13_5_1", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(12,4,1)+"wr_12_4_1", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(14,4,1)+"wr_14_4_1", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(12,3,1)+"wr_12_3_1", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(12,5,1)+"wr_12_5_1", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(14,3,1)+"wr_14_3_1", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(14,5,1)+"wr_14_5_1", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(13,4,0)+"wr_13_4_0", "up", 0, 0);
    add_swim_exit(SECTOR_PATH(13,4,2)+"wr_13_4_2", "down", 0, 2);
}
