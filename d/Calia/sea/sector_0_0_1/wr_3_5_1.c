/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/sea/std/sector_0_0_1_room";

void
create_water_room()
{
    make_the_room("\n", 3, 5, 1);

    add_swim_exit(SECTOR_PATH(3,4,1)+"wr_3_4_1", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(3,6,1)+"wr_3_6_1", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(2,5,1)+"wr_2_5_1", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(4,5,1)+"wr_4_5_1", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(2,4,1)+"wr_2_4_1", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(2,6,1)+"wr_2_6_1", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(4,4,1)+"wr_4_4_1", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(4,6,1)+"wr_4_6_1", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(3,5,0)+"wr_3_5_0", "up", 0, 0);
    add_swim_exit(SECTOR_PATH(3,5,2)+"wr_3_5_2", "down", 0, 2);
}
