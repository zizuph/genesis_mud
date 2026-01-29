/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/sea/std/sector_1_1_3_room";

void
create_water_room()
{
    make_the_room("\n", 11, 9, 3);

    add_swim_exit(SECTOR_PATH(11,8,3)+"wr_11_8_3", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(11,10,3)+"wr_11_10_3", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(10,9,3)+"wr_10_9_3", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(12,9,3)+"wr_12_9_3", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(10,8,3)+"wr_10_8_3", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(10,10,3)+"wr_10_10_3", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(12,8,3)+"wr_12_8_3", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(12,10,3)+"wr_12_10_3", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(11,9,2)+"wr_11_9_2", "up", 0, 0);
    add_swim_exit(SECTOR_PATH(11,9,4)+"wr_11_9_4", "down", 0, 2);
}
