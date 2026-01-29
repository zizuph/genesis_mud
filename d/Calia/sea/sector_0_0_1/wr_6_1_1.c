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
    make_the_room("\n", 6, 1, 1);

    add_swim_exit(SECTOR_PATH(6,0,1)+"wr_6_0_1", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(6,2,1)+"wr_6_2_1", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(5,1,1)+"wr_5_1_1", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(7,1,1)+"wr_7_1_1", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(5,0,1)+"wr_5_0_1", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(5,2,1)+"wr_5_2_1", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(7,0,1)+"wr_7_0_1", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(7,2,1)+"wr_7_2_1", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(6,1,0)+"wr_6_1_0", "up", 0, 0);
    add_swim_exit(SECTOR_PATH(6,1,2)+"wr_6_1_2", "down", 0, 2);
}
