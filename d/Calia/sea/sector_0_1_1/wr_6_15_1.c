/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.

*/

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/sea/std/sector_0_1_1_room";

void
create_water_room()
{
    make_the_room("\n", 6, 15, 1);

    add_swim_exit(SECTOR_PATH(6,14,1)+"wr_6_14_1", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(5,15,1)+"wr_5_15_1", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(7,15,1)+"wr_7_15_1", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(5,14,1)+"wr_5_14_1", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(7,14,1)+"wr_7_14_1", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(6,15,0)+"wr_6_15_0", "up", 0, 0);
    add_swim_exit(SECTOR_PATH(6,15,2)+"wr_6_15_2", "down", 0, 2);
}
