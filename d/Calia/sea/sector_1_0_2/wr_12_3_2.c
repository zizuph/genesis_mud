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
    make_the_room("\n", 12, 3, 2);

    add_swim_exit(SECTOR_PATH(12,2,2)+"wr_12_2_2", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(12,4,2)+"wr_12_4_2", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(11,3,2)+"wr_11_3_2", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(13,3,2)+"wr_13_3_2", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(11,2,2)+"wr_11_2_2", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(11,4,2)+"wr_11_4_2", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(13,2,2)+"wr_13_2_2", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(13,4,2)+"wr_13_4_2", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(12,3,1)+"wr_12_3_1", "up", 0, 0);
    add_swim_exit(SECTOR_PATH(12,3,3)+"wr_12_3_3", "down", 0, 2);
}
