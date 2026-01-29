/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/sea/std/sector_0_0_2_room";

void
create_water_room()
{
    make_the_room("\n", 6, 2, 2);

    add_swim_exit(SECTOR_PATH(6,1,2)+"wr_6_1_2", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(6,3,2)+"wr_6_3_2", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(5,2,2)+"wr_5_2_2", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(7,2,2)+"wr_7_2_2", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(5,1,2)+"wr_5_1_2", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(5,3,2)+"wr_5_3_2", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(7,1,2)+"wr_7_1_2", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(7,3,2)+"wr_7_3_2", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(6,2,1)+"wr_6_2_1", "up", 0, 0);
    add_swim_exit(SECTOR_PATH(6,2,3)+"wr_6_2_3", "down", 0, 2);
}
