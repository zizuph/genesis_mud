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
    make_the_room("\n", 8, 15, 2);

    add_swim_exit(SECTOR_PATH(8,14,2)+"wr_8_14_2", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(7,15,2)+"wr_7_15_2", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(9,15,2)+"wr_9_15_2", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(7,14,2)+"wr_7_14_2", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(9,14,2)+"wr_9_14_2", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(8,15,1)+"wr_8_15_1", "up", 0, 0);
    add_swim_exit(SECTOR_PATH(8,15,3)+"wr_8_15_3", "down", 0, 2);
}
