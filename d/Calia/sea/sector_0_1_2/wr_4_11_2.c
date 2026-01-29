/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/sea/std/sector_0_1_2_room";

void
create_water_room()
{
    make_the_room("\n", 4, 11, 2);

    add_swim_exit(SECTOR_PATH(4,10,2)+"wr_4_10_2", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(4,12,2)+"wr_4_12_2", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(3,11,2)+"wr_3_11_2", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(5,11,2)+"wr_5_11_2", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(3,10,2)+"wr_3_10_2", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(3,12,2)+"wr_3_12_2", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(5,10,2)+"wr_5_10_2", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(5,12,2)+"wr_5_12_2", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(4,11,1)+"wr_4_11_1", "up", 0, 0);
}
