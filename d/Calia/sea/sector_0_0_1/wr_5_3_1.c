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
    make_the_room("\n", 5, 3, 1);

    add_swim_exit(SECTOR_PATH(5,2,1)+"wr_5_2_1", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(5,4,1)+"wr_5_4_1", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(4,3,1)+"wr_4_3_1", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(6,3,1)+"wr_6_3_1", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(4,2,1)+"wr_4_2_1", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(4,4,1)+"wr_4_4_1", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(6,2,1)+"wr_6_2_1", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(6,4,1)+"wr_6_4_1", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(5,3,0)+"wr_5_3_0", "up", 0, 0);
    add_swim_exit(SECTOR_PATH(5,3,2)+"wr_5_3_2", "down", 0, 2);
}
