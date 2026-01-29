/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/sea/std/sector_0_0_3_room";

void
create_water_room()
{
    make_the_room("\n", 6, 1, 3);

    add_swim_exit(SECTOR_PATH(6,0,3)+"wr_6_0_3", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(6,2,3)+"wr_6_2_3", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(5,1,3)+"wr_5_1_3", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(7,1,3)+"wr_7_1_3", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(5,0,3)+"wr_5_0_3", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(5,2,3)+"wr_5_2_3", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(7,0,3)+"wr_7_0_3", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(7,2,3)+"wr_7_2_3", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(6,1,2)+"wr_6_1_2", "up", 0, 0);
    add_swim_exit(SECTOR_PATH(6,1,4)+"wr_6_1_4", "down", 0, 2);
}
