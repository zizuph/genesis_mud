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
    make_the_room("\n", 9, 13, 3);

    add_swim_exit(SECTOR_PATH(9,12,3)+"wr_9_12_3", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(9,14,3)+"wr_9_14_3", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(8,13,3)+"wr_8_13_3", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(10,13,3)+"wr_10_13_3", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(8,12,3)+"wr_8_12_3", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(8,14,3)+"wr_8_14_3", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(10,12,3)+"wr_10_12_3", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(10,14,3)+"wr_10_14_3", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(9,13,2)+"wr_9_13_2", "up", 0, 0);
    add_swim_exit(SECTOR_PATH(9,13,4)+"wr_9_13_4", "down", 0, 2);
}
