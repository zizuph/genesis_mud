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
    make_the_room("\n", 9, 11, 3);

    add_swim_exit(SECTOR_PATH(9,10,3)+"wr_9_10_3", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(9,12,3)+"wr_9_12_3", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(8,11,3)+"wr_8_11_3", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(10,11,3)+"wr_10_11_3", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(8,10,3)+"wr_8_10_3", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(8,12,3)+"wr_8_12_3", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(10,10,3)+"wr_10_10_3", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(10,12,3)+"wr_10_12_3", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(9,11,2)+"wr_9_11_2", "up", 0, 0);
    add_swim_exit(SECTOR_PATH(9,11,4)+"wr_9_11_4", "down", 0, 2);
}
