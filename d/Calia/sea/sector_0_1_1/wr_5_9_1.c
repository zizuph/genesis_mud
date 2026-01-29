/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/sea/std/sector_0_1_1_room";

void
create_water_room()
{
    make_the_room("\n", 5, 9, 1);

    add_swim_exit(SECTOR_PATH(5,8,1)+"wr_5_8_1", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(5,10,1)+"wr_5_10_1", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(4,9,1)+"wr_4_9_1", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(6,9,1)+"wr_6_9_1", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(4,8,1)+"wr_4_8_1", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(4,10,1)+"wr_4_10_1", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(6,8,1)+"wr_6_8_1", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(6,10,1)+"wr_6_10_1", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(5,9,0)+"wr_5_9_0", "up", 0, 0);
    add_swim_exit(SECTOR_PATH(5,9,2)+"wr_5_9_2", "down", 0, 2);
}
