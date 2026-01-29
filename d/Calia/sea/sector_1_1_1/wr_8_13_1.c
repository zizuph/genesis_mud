/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/sea/std/sector_1_1_1_room";

void
create_water_room()
{
    make_the_room("\n", 8, 13, 1);

    add_swim_exit(SECTOR_PATH(8,12,1)+"wr_8_12_1", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(8,14,1)+"wr_8_14_1", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(7,13,1)+"wr_7_13_1", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(9,13,1)+"wr_9_13_1", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(7,12,1)+"wr_7_12_1", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(7,14,1)+"wr_7_14_1", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(9,12,1)+"wr_9_12_1", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(9,14,1)+"wr_9_14_1", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(8,13,0)+"wr_8_13_0", "up", 0, 0);
    add_swim_exit(SECTOR_PATH(8,13,2)+"wr_8_13_2", "down", 0, 2);
}
