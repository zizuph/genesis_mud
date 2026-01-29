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
    make_the_room("\n", 8, 15, 3);

    add_swim_exit(SECTOR_PATH(8,14,3)+"wr_8_14_3", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(7,15,3)+"wr_7_15_3", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(9,15,3)+"wr_9_15_3", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(7,14,3)+"wr_7_14_3", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(9,14,3)+"wr_9_14_3", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(8,15,2)+"wr_8_15_2", "up", 0, 0);
    add_swim_exit(SECTOR_PATH(8,15,4)+"wr_8_15_4", "down", 0, 2);
}
