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
    make_the_room("\n", 10, 11, 2);

    add_swim_exit(SECTOR_PATH(10,10,2)+"wr_10_10_2", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(10,12,2)+"wr_10_12_2", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(9,11,2)+"wr_9_11_2", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(11,11,2)+"wr_11_11_2", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(9,10,2)+"wr_9_10_2", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(9,12,2)+"wr_9_12_2", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(11,10,2)+"wr_11_10_2", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(11,12,2)+"wr_11_12_2", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(10,11,1)+"wr_10_11_1", "up", 0, 0);
    add_swim_exit(SECTOR_PATH(10,11,3)+"wr_10_11_3", "down", 0, 2);
}
