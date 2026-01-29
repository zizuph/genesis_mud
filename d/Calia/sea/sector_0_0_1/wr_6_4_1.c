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
    make_the_room("\n", 6, 4, 1);

    add_swim_exit(SECTOR_PATH(6,3,1)+"wr_6_3_1", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(6,5,1)+"wr_6_5_1", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(5,4,1)+"wr_5_4_1", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(7,4,1)+"wr_7_4_1", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(5,3,1)+"wr_5_3_1", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(5,5,1)+"wr_5_5_1", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(7,3,1)+"wr_7_3_1", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(7,5,1)+"wr_7_5_1", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(6,4,0)+"wr_6_4_0", "up", 0, 0);
    add_swim_exit(SECTOR_PATH(6,4,2)+"wr_6_4_2", "down", 0, 2);
}
