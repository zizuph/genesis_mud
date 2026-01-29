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
    make_the_room("\n", 4, 13, 1);

    add_swim_exit(SECTOR_PATH(4,12,1)+"wr_4_12_1", "north", 0, 1);
    add_swim_exit(SECTOR_PATH(4,14,1)+"wr_4_14_1", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(3,13,1)+"wr_3_13_1", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(5,13,1)+"wr_5_13_1", "west", 0, 1);
    add_swim_exit(SECTOR_PATH(3,12,1)+"wr_3_12_1", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(3,14,1)+"wr_3_14_1", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(5,12,1)+"wr_5_12_1", "northwest", 0, 1);
    add_swim_exit(SECTOR_PATH(5,14,1)+"wr_5_14_1", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(4,13,0)+"wr_4_13_0", "up", 0, 0);
    add_swim_exit(SECTOR_PATH(4,13,2)+"wr_4_13_2", "down", 0, 2);
}
