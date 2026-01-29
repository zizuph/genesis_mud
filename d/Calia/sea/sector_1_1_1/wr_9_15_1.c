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
    make_the_room("\n", 9, 15, 1);

    add_swim_exit(SECTOR_PATH(9,14,1)+"wr_9_14_1", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(8,15,1)+"wr_8_15_1", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(10,15,1)+"wr_10_15_1", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(8,14,1)+"wr_8_14_1", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(10,14,1)+"wr_10_14_1", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(9,15,0)+"wr_9_15_0", "up", 0, 0);
    add_swim_exit(SECTOR_PATH(9,15,2)+"wr_9_15_2", "down", 0, 2);
}
