/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/sea/std/sector_1_1_2_room";

void
create_water_room()
{
    make_the_room("\n", 9, 8, 2);

    add_swim_exit(SECTOR_PATH(9,7,2)+"wr_9_7_2", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(9,9,2)+"wr_9_9_2", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(8,8,2)+"wr_8_8_2", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(10,8,2)+"wr_10_8_2", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(8,7,2)+"wr_8_7_2", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(8,9,2)+"wr_8_9_2", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(10,7,2)+"wr_10_7_2", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(10,9,2)+"wr_10_9_2", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(9,8,1)+"wr_9_8_1", "up", 0, 0);
    add_swim_exit(SECTOR_PATH(9,8,3)+"wr_9_8_3", "down", 0, 2);
}
