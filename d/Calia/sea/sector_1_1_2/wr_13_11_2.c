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
    make_the_room("\n", 13, 11, 2);

    add_swim_exit(SECTOR_PATH(13,10,2)+"wr_13_10_2", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(13,12,2)+"wr_13_12_2", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(12,11,2)+"wr_12_11_2", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(14,11,2)+"wr_14_11_2", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(12,10,2)+"wr_12_10_2", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(12,12,2)+"wr_12_12_2", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(14,10,2)+"wr_14_10_2", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(14,12,2)+"wr_14_12_2", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(13,11,1)+"wr_13_11_1", "up", 0, 0);
    add_swim_exit(SECTOR_PATH(13,11,3)+"wr_13_11_3", "down", 0, 2);
}
