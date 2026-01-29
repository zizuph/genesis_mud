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
    make_the_room("\n", 7, 9, 2);

    add_swim_exit(SECTOR_PATH(7,8,2)+"wr_7_8_2", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(7,10,2)+"wr_7_10_2", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(6,9,2)+"wr_6_9_2", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(8,9,2)+"wr_8_9_2", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(6,8,2)+"wr_6_8_2", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(6,10,2)+"wr_6_10_2", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(8,8,2)+"wr_8_8_2", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(8,10,2)+"wr_8_10_2", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(7,9,1)+"wr_7_9_1", "up", 0, 0);
    add_swim_exit(SECTOR_PATH(7,9,3)+"wr_7_9_3", "down", 0, 2);
}
